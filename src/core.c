#include "core.h"
core(CAR,1) car(obj_t *obj)
{
	if (obj->type==CELL)
		return (obj_t *)obj->car;
	return &ERROR_OBJ;
}
core(CDR,1) cdr(obj_t *obj)
{
	if (obj->type==CELL)
		return (obj_t *)obj->cdr;
	return &ERROR_OBJ;
}
core(CONS,2) cons(obj_t *obj1,obj_t *obj2)
{
	inc_rc(obj1);
	inc_rc(obj2);
	return new_obj(CELL,(long)obj1,(long)obj2);
}
core(OUTPUT,1) output(obj_t *obj)
{
	print_obj(obj,stdout,true);
	return obj;
}
core(PRINT,1) print(obj_t *obj)
{
	print_obj(obj,stdout,false);
	return obj;
}
void print_obj(obj_t *obj,FILE *fh,bool q)
{
	switch (obj->type) {
	case CELL:
		print_cell(obj,fh,q);
		break;
	case SYMBOL:
		if (q&&obj->cdr)
			fprintf(fh,"\"%s\"",(char *)obj->car);
		else
			fprintf(fh,"%s",(char *)obj->car);
		break;
	case INTEGER:
		fprintf(fh,"%ld",obj->car);
		break;
	case FUNCTION:
		fprintf(fh,"{FUNCTION 0x%lx}",(long)obj);
		break;
	case DOUBLE:
		fprintf(fh,"%lf",((dobj_t *)obj)->car);
		break;
	case ERROR:
		fprintf(fh,"{ERROR}");
		break;
	default:
		fprintf(fh,"{UNKNOWN TYPE}");
	}
}
void print_cell(obj_t *obj,FILE *fh,bool q)
{
	fputc('(',fh);
	obj_t *o=obj;
	while (o!=NIL) {// TODO: Abstract
		if (o->type!=CELL) {
			fputs(". ",fh);
			print_obj(o,fh,q);
			fputc(')',fh);
			return;
		}
		print_obj(car(o),fh,q);
		if ((obj_t *)o->cdr!=NIL)
			fputc(' ',fh);
		o=(obj_t *)o->cdr;
	}
	fputc(')',fh);
}
core(TERPRI,0) terpri()
{
	putchar('\n');
	return NIL;
}
core(EQ,2) eq(obj_t *obj1,obj_t *obj2)
{
	if (obj1==obj2)
		return T;
	// The addresses are not equal
	if (obj1->type!=obj2->type)
		return NIL;
	// The types are equal
	switch (obj1->type) {
	case SYMBOL:
		return strcasecmp((char *)obj1->car,(char *)obj2->car)?NIL:T;
	case INTEGER:
	case DOUBLE:
		return obj1->car==obj2->car?T:NIL;
	default:
		return NIL;
	}
}
core(SET,2) set(obj_t *obj1,obj_t *obj2)
{
	if (obj1->refs<0)
		return &ERROR_OBJ;
	// Free memory from old contents if appropriate
	switch (obj1->type) {
	case CELL:
		dec_rc((obj_t *)obj1->car);
		dec_rc((obj_t *)obj1->cdr);
		break;
	case FUNCTION:
		destroy_body(obj1);
		break;
	case SYMBOL:
		free((void *)obj1->car);
	default:
		break;
	}
	// Prepare new memory areas if appropriate
	switch (obj2->type) {
	case SYMBOL:
		obj1->car=(long)calloc(strlen((char *)obj2->car)+1,1);
		strcpy((char *)obj1->car,(char *)obj2->car);
		break;
	case FUNCTION:
		obj1->car=(long)malloc(obj2->cdr); // Allocate body
		obj1->cdr=obj2->cdr; // Copy size
		memcpy((void *)obj1->car,(void *)obj2->car,obj2->cdr); // Copy pointers
		for (long i=0;i<obj2->cdr;i++) // Increase reference counters
			inc_rc(((obj_t **)obj1->car)[i]);
		break;
	case CELL:
		inc_rc((obj_t *)obj2->car);
		inc_rc((obj_t *)obj2->cdr);
	default:
		obj1->car=obj2->car;
	}
	obj1->type=obj2->type;
	obj1->cdr=obj2->cdr;
	return obj1;
}
core(RPLACA,2) rplaca(obj_t *obj1,obj_t *obj2)
{
	if (obj1->refs<0||obj1->type!=CELL)
		return &ERROR_OBJ;
	dec_rc((obj_t *)obj1->car);
	inc_rc(obj2);
	obj1->car=(long)obj2;
	return obj1;
}
core(RPLACD,2) rplacd(obj_t *obj1,obj_t *obj2)
{
	if (obj1->refs<0||obj1->type!=CELL)
		return &ERROR_OBJ;
	dec_rc((obj_t *)obj1->cdr);
	inc_rc(obj2);
	obj1->cdr=(long)obj2;
	return obj1;
}
obj_t *lread(long n) // lread - read(long)
{
	char str[n];
	fgets(str,n,stdin);
	str[strlen(str)-1]='\0';
	return to_obj(str);
}
core(READ,1) oread(obj_t *obj) // oread - read(object)
{
	if (obj->type!=INTEGER)
		return &ERROR_OBJ;
	return lread(obj->car);
}
core(ATOM,1) atom(obj_t *obj)
{
	return obj->type==CELL?NIL:T;
}
core(NULL,1) null(obj_t *obj)
{
	return obj==NIL?T:NIL;
}
core(NCONC,2) nconc(obj_t *obj1,obj_t *obj2)
{
	if (obj1->type!=CELL)
		return &ERROR_OBJ;
	obj_t *o=obj1;
	for (;cdr(o)->type==CELL;o=(obj_t *)o->cdr);
	rplacd(o,obj2);
	return obj1;
}
core(COPY,1) copy(obj_t *obj)
{
	obj_t *c;
	if (obj->refs<0)
		return obj;
	switch (obj->type) {
	case CELL:
		return cons(copy(car(obj)),copy(cdr(obj)));
	default:
		c=new_obj(ERROR,0,0);
		return set(c,obj);
	}
}
core(APPEND,2) append(obj_t *obj1,obj_t *obj2)
{
	return nconc(copy(obj1),obj2);
}
core(ASSOC,2) assoc(obj_t *sym,obj_t *list)
{
	if (list->type!=CELL)
		return &ERROR_OBJ;
	for (obj_t *o=list;o!=NIL;o=cdr(o))
		if (eq(sym,car(car(o)))==T)
			return car(o);
	return NIL;
}
core(DECLARE,2) declare(obj_t *sym,obj_t *def)
{
	if (sym->refs<0)
		return &ERROR_OBJ;
	DICT=cons(cons(sym,def),DICT);
	return sym;
}
core(DEFINE,2) define(obj_t *sym,obj_t *def)
{
	if (sym->refs<0&&sym!=RECURSE&&sym!=ARGV)
		return &ERROR_OBJ;
	ENV=cons(cons(sym,def),ENV);
	return sym;
}
core(SYMVAL,1) symval(obj_t *obj)
{
	if (obj->refs<0&&obj!=RECURSE&&obj!=ARGV)
		return obj;
	if (obj->type!=SYMBOL)
		return obj;
	obj_t *def=assoc(obj,DICT);
	if (def!=NIL)
		return cdr(def);
	def=assoc(obj,ENV);
	if (def!=NIL)
		return cdr(def);
	return &ERROR_OBJ;
}
core(EXIT,0) l_exit()
{
	while (stackitem(0))
		dec_rc(pop());
	//dec_rc(ENV);
	dec_rc(DICT);
	exit(0);
}
core(LIST,0) list()
{
	push(NIL);
	while(stackitem(1)!=&ARGS)
		s_cons();
	register obj_t *r=pop();
	r->refs-=r->refs>0;
	return r;
}
long length(obj_t *list)
{
	if (list->type!=CELL)
		return 0;
	long c=0;
	for (;list!=NIL;list=cdr(list))
		c++;
	return c;
}
core(LENGTH,1) l_length(obj_t *list)
{
	return new_obj(INTEGER,length(list),0);
}
core(LAMBDA,2) lambda(obj_t *args,obj_t *body)
{
	obj_t *rpf=rpn(body),*o=rpf;
	long size=2+length(rpf);
	obj_t **f=malloc(sizeof(obj_t *)*size);
	f[0]=ENV;
	inc_rc(ENV);
	f[1]=args;
	inc_rc(args);
	for (int i=2;i<size;i++) {
		f[i]=car(o);
		inc_rc(f[i]);
		o=cdr(o);
	}
	if (!rpf->refs)
		destroy(rpf);
	return new_obj(FUNCTION,(long)f,size);
}
core(SEE,1) see(obj_t *func)
{
	if (func->type!=FUNCTION&&func->refs<0)
		return func;
	long size=func->cdr;
	obj_t **f=(obj_t **)func->car;
	obj_t *list=NIL;
	for (int i=size-1;i>1;i--)
		list=cons(f[i]->type==FUNCTION?see(f[i]):f[i],list);
	list=cons(f[0],cons(f[1],cons(list,NIL)));
	return list;
}
void bind_args(obj_t *argn)
{	// Bind symbols in list to items on stack
	if (argn==VARIADIC) {
		define(ARGV,list());
		return;
	}
	obj_t *l=argn;
	long argc=length(argn);
	for (long i=0;i<argc;i++) {
		define(car(l),stackitem(argc-1-i));
		dec_rc(stackitem(argc-1-i));
		l=cdr(l);
	}
	ndrop(argc);
}
obj_t *funcall(obj_t *func)
{
	if (func->type!=FUNCTION)
		return &ERROR_OBJ;
	if (func->refs<0) {
		void (*cf)()=(void *)func->car;
		cf();
		goto RETURN_TOS;
	}
	obj_t **f=(obj_t **)func->car;
	obj_t *old_env=ENV;
	ENV=f[0];
	bind_args(f[1]);
	define(RECURSE,func);
	do_body(f,func->cdr);
	dec_rc(ENV);
	ENV=old_env;
RETURN_TOS:
	stackitem(0)->refs-=stackitem(0)->refs>0;
	return pop();
}
void do_body(obj_t **b,long size)
{
	for (int i=2;i<size;i++) { // TODO: Abstract
		obj_t *obj=b[i];
		if (obj==&ARGS) {
			push(&ARGS);
		} else if (obj==&CALL) {
			obj_t *f=pop();
			push(funcall(f));
			dec_rc(f);
			nip(); // Remove <ARGS>
		} else if (obj==&DROP) {
			dec_rc(pop());
		} else if (obj==&COND_END) {
			push(NIL);
		} else if (obj==&COND_DO) {
			obj_t *o=pop();
			i++;
			if (o!=NIL) {
				do_body((obj_t **)b[i]->car,b[i]->cdr);
				for (;b[i]!=&COND_END;i++);
			}
			dec_rc(o);
		} else if (obj==QUOTE) {
			push(b[i+1]);
			i++;
		} else
			push(symval(obj));
	}
}
char *slurp(char *file)
{
	FILE *fs=fopen(file,"r");
	if (!fs)
		return NULL;
	fseek(fs,0,SEEK_END);
	long size=ftell(fs);
	rewind(fs);
	char *str=calloc(size+1,1);
	fread(str,1,size,fs);
	fclose(fs);
	return str;
}
core(LOAD,1) load(obj_t *obj)
{
	if (obj->type!=SYMBOL)
		return &ERROR_OBJ;
	char *file=slurp((char *)obj->car);
	if (!file)
		return &ERROR_OBJ;
	obj_t *o=to_obj(file);
	free(file);
	return o;
}
core(EVAL,1) eval(obj_t *obj)
{
	DEBUG(fprintf(stderr,"EVAL: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	obj_t *f=lambda(NIL,obj);
	do_body((obj_t **)f->car,f->cdr);
	dec_rc(f);
	obj_t *r=pop();
	r->refs-=r->refs>0;
	return r;
}
core(TYPE,1) type(obj_t *obj)
{
	return type_objs[obj->type];
}
core(TYPEP,2) typep(obj_t *obj,obj_t *type)
{
	return eq(type_objs[obj->type],type);
}
core(OR,2) or(obj_t *a,obj_t *b)
{
	return a!=NIL||b!=NIL?T:NIL;
}
core(AND,2) and(obj_t *a,obj_t *b)
{
	return a!=NIL&&b!=NIL?T:NIL;
}
core(NOT,2) not(obj_t *obj)
{
	return null(obj);
}
core(FILE-OUT,2) file_out(obj_t *file,obj_t *obj)
{
	if (file->type!=SYMBOL)
		return &ERROR_OBJ;
	FILE *fh=fopen((char *)file->car,"w");
	if (!fh)
		return &ERROR_OBJ;
	print_obj(obj,fh,true);
	fclose(fh);
	return obj;
}
core(NTHCDR,2) nthcdr(obj_t *num,obj_t *list)
{
	if (num->type!=INTEGER||list->type!=CELL)
		return &ERROR_OBJ;
	long n=num->car;
	for (long i=0;i<n;i++)
		list=cdr(list);
	return list;
}
core(SYSTEM,1) l_system(obj_t *o)
{
	if (o->type!=SYMBOL)
		return &ERROR_OBJ;
	return new_obj(INTEGER,system((char *)o->car),0);
}
core(SYMCONC,2) symconc(obj_t *sym1,obj_t *sym2)
{
	if (sym1->type!=SYMBOL||sym2->type!=SYMBOL)
		return &ERROR_OBJ;
	char *str1=(char *)sym1->car,*str2=(char *)sym2->car;
	char *s=calloc(strlen(str1)+strlen(str2)+1,1);
	strcat(s,str1);
	strcat(s,str2);
	return new_obj(SYMBOL,(long)s,sym1->cdr||sym2->cdr);
}
core(KEY,0) key()
{
	struct termios term;
	tcgetattr(0,&term);
	term.c_lflag&=~(ICANON|ECHO);
	tcsetattr(0,TCSANOW,&term);
	printf("\e[?25l");
	obj_t *o=new_obj(INTEGER,fgetc(stdin),0);
	printf("\e[?25h");
	term.c_lflag|=(ICANON|ECHO);
	tcsetattr(0,TCSANOW,&term);
	return o;
}
core(SLEEP,1) l_sleep(obj_t *t)
{
	if (t->type!=DOUBLE&&t->type!=INTEGER)
		return &ERROR_OBJ;
	if (t->car<0)
		return &ERROR_OBJ;
	if (t->type==DOUBLE)
		usleep((int)((dobj_t *)t)->car*1000000);
	else if (t->type==INTEGER)
		usleep((int)t->car*1000000);
	return NIL;
}
core(READ-LINE,1) readline(obj_t *bufsize)
{
	if (bufsize->type!=INTEGER)
		return &ERROR_OBJ;
	char *buf=calloc(bufsize->car+1,1);
	fgets(buf,bufsize->car,stdin);
	buf[strlen(buf)-1]='\0'; // Remove newline
	return new_obj(SYMBOL,(long)buf,1);
}
