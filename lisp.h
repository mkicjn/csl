#ifndef LISP_H
#define LISP_H
#include <stdlib.h>
// Type definitions
typedef enum {false,true} bool;
typedef enum {CELL,SYMBOL,INTEGER,FUNCTION,DOUBLE,ERROR} type_t;
const char *types[6]={
	"CELL",
	"SYMBOL",
	"INTEGER",
	"FUNCTION",
	"DOUBLE",
	"ERROR"
};
typedef struct {
	type_t type;
	long car,cdr;
	int refs;
} obj_t;
typedef struct {
	type_t type;
	double car,cdr;
	int refs;
} dobj_t; // To avoid typecasting double->long
// Memory management
#define new(x) malloc(sizeof(x));
obj_t *new_obj(type_t type,long car,long cdr)
{
	obj_t *obj=new(obj_t);
	obj->type=type;
	obj->car=car;
	obj->cdr=cdr;
	obj->refs=0;
	return obj;
}
obj_t *new_dobj(double car)
{	// This function exists to circumvent implicit typecasting
	obj_t *obj=new(obj_t);
	obj->type=DOUBLE;
	((dobj_t *)obj)->car=car;
	obj->cdr=0;
	obj->refs=0;
	return (obj_t *)obj;
}
void dec_rc(obj_t *);
void destroy_func(obj_t *);
void destroy(obj_t *obj)
{
	switch (obj->type) {
	case FUNCTION:
		destroy_func(obj);
		break;
	case SYMBOL:
		free((char *)obj->car);
	case DOUBLE:
	case INTEGER:
		free(obj);
		break;
	case CELL:
		dec_rc((obj_t *)obj->car);
		dec_rc((obj_t *)obj->cdr);
		free(obj);
	default:
		break;
	}
}
void destroy_func(obj_t *obj)
{
	long size=obj->cdr;
	obj_t **f=(obj_t **)obj->car;
	for (int i=0;i<size;i++)
		dec_rc(f[i]);
	free(f);
	free(obj);
}
void rcdestroy(obj_t *obj)
{
	if (obj->refs==0)
		destroy(obj);
}
void inc_rc(obj_t *obj)
{
	if (0xff>(long)obj)
		return;
	obj->refs+=obj->refs>=0;
}
void dec_rc(obj_t *obj)
{
	if (0xff>(long)obj)
		return;
	obj->refs-=obj->refs>0;
	if (obj->refs==0)
		destroy(obj);
}
// Constants
#define CONSTANT(x) {	\
	.type=SYMBOL,	\
	.car=(long)#x,	\
	.cdr=0,		\
	.refs=-1	\
}
obj_t NIL_OBJ=CONSTANT(NIL);
obj_t *NIL=&NIL_OBJ;
obj_t T_OBJ=CONSTANT(T);
obj_t *T=&T_OBJ;
obj_t SELF_OBJ=CONSTANT(@);
obj_t *SELF=&SELF_OBJ;
obj_t QUOTE_OBJ=CONSTANT(QUOTE);
obj_t *QUOTE=&QUOTE_OBJ;
obj_t *ENV=&NIL_OBJ;
obj_t ARGS=CONSTANT(<ARGS>); // Exists so special forms know where their arguments end
obj_t CALL=CONSTANT(<CALL>); // Exists to tell `funcall` when to call vs. push a function
// LISP core functions
#define core(name,argc) obj_t * // Info for dictionary code generator
core(CAR,1) car(obj_t *obj)
{
	if (obj->type==CELL)
		return (obj_t *)obj->car;
	return NIL;
}
core(CDR,1) cdr(obj_t *obj)
{
	if (obj->type==CELL)
		return (obj_t *)obj->cdr;
	return NIL;
}
core(CONS,2) cons(obj_t *obj1,obj_t *obj2)
{
	inc_rc(obj1);
	inc_rc(obj2);
	return new_obj(CELL,(long)obj1,(long)obj2);
}
void print_cell(obj_t *);
core(PRINT,1) print(obj_t *obj)
{
	switch (obj->type) {
	case CELL:
		print_cell(obj);
		break;
	case SYMBOL:
		printf("%s",(char *)obj->car);
		break;
	case INTEGER:
		printf("%ld",obj->car);
		break;
	case FUNCTION:
		printf("{FUNCTION 0x%lx}",(long)obj);
		break;
	case DOUBLE:
		printf("%lf",((dobj_t *)obj)->car);
		break;
	default:
		printf("{ERROR}");
	}
	return obj;
}
void print_cell(obj_t *obj)
{
	putchar('(');
	obj_t *o=obj;
	while (o!=NIL) {
		if (o->type!=CELL) {
			fputs(". ",stdout);
			print(o);
			putchar(')');
			return;
		}
		print(car(o));
		if ((obj_t *)o->cdr!=NIL)
			putchar(' ');
		o=(obj_t *)o->cdr;
	}
	putchar(')');
}
core(TERPRI,0) terpri() {
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
		return NIL;
	// Free memory from old contents if appropriate
	switch (obj1->type) {
	case CELL:
		dec_rc((obj_t *)obj1->car);
		dec_rc((obj_t *)obj1->cdr);
		break;
	case FUNCTION:
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
		obj1->car=(long)malloc(obj2->cdr);
		obj1->cdr=obj2->cdr;
		memcpy((void *)obj1->car,(void *)obj2->car,obj2->cdr);
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
	if (obj1->refs<0)
		return NIL;
	dec_rc((obj_t *)obj1->car);
	inc_rc(obj2);
	obj1->car=(long)obj2;
	return obj1;
}
core(RPLACD,2) rplacd(obj_t *obj1,obj_t *obj2)
{
	if (obj1->refs<0)
		return NIL;
	dec_rc((obj_t *)obj1->cdr);
	inc_rc(obj2);
	obj1->cdr=(long)obj2;
	return obj1;
}
extern obj_t *to_obj(char *);
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
		return NIL;
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
		return NIL;
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
	for (obj_t *o=list;o!=NIL;o=cdr(o))
		if (eq(sym,car(car(o)))==T)
			return car(o);
	return NIL;
}
extern obj_t *DICT;
core(DECLARE,2) declare(obj_t *sym,obj_t *def)
{
	obj_t *cdef=assoc(sym,DICT);
	if (cdr(cdef)==NIL) {
		DICT=cons(cons(sym,def),DICT);
	} else {
		rplacd(cdef,def);
	}
	return sym;
}
core(DEFINE,2) define(obj_t *sym,obj_t *def)
{
	obj_t *cdef=assoc(sym,ENV);
	if (cdr(cdef)==NIL) {
		ENV=cons(cons(sym,def),ENV);
	} else {
		rplacd(cdef,def);
	}
	return sym;
}
extern obj_t *stackitem(int);
extern void drop();
core(EXIT,0) l_exit()
{
	while (stackitem(0))
		drop();
	dec_rc(ENV);
	dec_rc(DICT);
	exit(0);
}
extern void s_cons();
extern void push();
extern obj_t *pop();
core(LIST,0) list()
{
	push(NIL);
	while(stackitem(1)!=&ARGS)
		s_cons();
	register obj_t *r=pop();
	r->refs--;
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
extern obj_t *rpn(obj_t *);
core(LAMBDA,2) lambda(obj_t *args,obj_t *body)
{
	obj_t *rpf=rpn(body),*o=rpf;
	long size=2+length(rpf);
	obj_t **f=malloc(sizeof(obj_t *)*size);
	f[0]=args;
	inc_rc(args);
	f[1]=ENV;
	inc_rc(ENV);
	for (int i=2;i<size;i++) {
		f[i]=car(o);
		inc_rc(f[i]);
		o=cdr(o);
	}
	destroy(rpf);
	return new_obj(FUNCTION,(long)f,size);
}
core(SEE,1) see(obj_t *func)
{
	long size=func->cdr;
	obj_t **f=(obj_t **)func->car;
	obj_t *list=NIL;
	for (int i=size-1;i>1;i--)
		list=cons(f[i],list);
	list=cons(f[0],cons(list,NIL));
	return list;
}
core(SYMVAL,1) symval(obj_t *obj)
{
	if (obj->type!=SYMBOL)
		return obj;
	obj_t *gdef=assoc(obj,DICT);
	if (gdef!=NIL)
		return cdr(gdef);
	return cdr(assoc(obj,ENV));
}
extern void nip();
core(FUNCALL,1) funcall(obj_t *func)
{
	if (func->refs<0) {
		void (*cf)()=(void *)func->car;
		cf();
		goto RETURN_TOS;
	}
	obj_t **f=(obj_t **)func->car;
	obj_t *argn=f[0];
	obj_t *old_env=ENV;
	ENV=f[1];
	// To-do: Bind arguments
	long size=func->cdr;
	for (int i=2;i<size;i++) {
		obj_t *obj=f[i];
		if (obj==&ARGS)
			push(&ARGS);
		else if (obj==&CALL) {
			obj_t *f=pop();
			push(funcall(f));
			dec_rc(f);
			nip(); // Remove <ARGS>
		} else if (obj==QUOTE) {
			push(f[i+1]);
			i++;
		} else
			push(symval(obj));
	}
RETURN_TOS:
	stackitem(0)->refs-=stackitem(0)->refs>0;
	ENV=old_env;
	return pop();
}

#endif
