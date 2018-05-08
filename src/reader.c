#include "reader.h"
char *ltrim(char *s)
{
	for (;*s==' '||*s=='\n'||*s=='\t';s++);
	switch (*s) {
	case '~':
		s++;
		for (;*s!='~';s++);
		return ltrim(s+1);
	case '#':
		s++;
		for (;*s!='\n';s++);
		return ltrim(s+1);
	default:
		return s;
	}
}
bool valid_list(char *s)
{
	int p=0;
	bool q=*s=='"';
	for (;*s;s++) {
		if (*s=='"')
			q=!q;
		if (q)
			continue;
		if (*s=='('||*s=='{')
			p++;
		else if (*s==')'||*s=='}')
			p--;
	}
	return p==0;
}
type_t infer_type(char *s)
{
	if (!s)
		return ERROR;
	s+=*s=='\''||*s=='`'; // Skip backtick or apostrophe
	if (*s=='"')
		return SYMBOL;
	if (*s=='('||*s=='{')
		return valid_list(s)?CELL:ERROR;
	if (*s=='-') {
		s++;
		if (!*s)
			return SYMBOL;
	}
	bool d=false;
	for (;*s;s++) {
		if (*s>='0'&&*s<='9')
			continue;
		if (*s=='.') {
			if (d)
				return SYMBOL;
			d=true;
			continue;
		}
		return SYMBOL;
	}
	return d?DOUBLE:INTEGER;
}
char *get_word(char *s)
{
	register int c=0;
	if (*s=='"') {
		for (;s[c+1]&&s[c+1]!='"';c++);
		if (s[c+1]!='"')
			return NULL;
		return memcpy(calloc(c+1,1),s+1,c);
	}
	for (;s[c]&&s[c]!=' '&&s[c]!='\t'&&s[c]!='\n'&&s[c]!=')'&&s[c]!='}';c++); // Count characters
	if (!c)
		return NULL;
	return memcpy(calloc(c+1,1),s,c);
}
char *get_list(char *s)
{
	register int c=0,p=0;
	for (;s[c];c++) { // Count parentheses
		if (s[c]=='('||s[c]=='{')
			p++;
		else if (s[c]==')'||s[c]=='}') {
			p--;
			if (!p) // Exit when balanced
				goto GET_LIST_RET;
		}
	}
	return NULL;
GET_LIST_RET:
	return memcpy(calloc(c+2,1),s,c+1);
}
char *get_token(char *s)
{
	s=ltrim(s);
	if (!*s)
		return NULL;
	if (*s=='\''||*s=='`')
		s++;
	if (*s=='"')
		return get_word(s);
	if (*s=='('||*s=='{')
		return get_list(s);
	return get_word(s);
}
obj_t *quote(obj_t *obj)
{
	if (obj==NIL||obj==T)
		return obj;
	return cons(QUOTE,cons(obj,NIL));
}
obj_t *to_list(char *s)
{
	push(NULL); // Marker for front of list
	bool dot=false;
	bool m=*s=='{';
	if (*s=='\'')
		s++;
	s++;
	int c=0;
	while (*s&&*(s=ltrim(s))!=')'&&*s!='}') {
		bool q=*s=='\''||(m&&c>0);
		bool bq=*s=='`',qm=s[q]=='"';
		char *tok=get_token(s);
		if (!tok)
			break;
		int len=strlen(tok);
		if (bq) {
			push(to_splice(tok+1));
			goto T_L_NEXT_TOK;
		}
		if (tok[0]=='.'&&!tok[1]) {
			dot=true;
			free(tok);
			s++;
			continue;
		}
		obj_t *p=qm?new_obj(SYMBOL,(long)tok,1):to_obj(tok);
		push(q?quote(p):p);
T_L_NEXT_TOK:
		if (!qm)
			free(tok);
		if (dot)
			break;
		s+=len+q+bq+qm+qm;
		c++;
	}
	if (!dot)
		push(NIL);
	while (stackitem(1))
		s_cons();
	obj_t *list=pop();
	pop(); // Get rid of NULL on stack
	list->refs--;
	if (m) // If it is a "macro evaluation"
		list=cons(&eval_fun,cons(list,NIL)); // (cons eval (cons list nil))
	return list;
}
obj_t *to_obj(char *s)
{
	obj_t *obj;
	bool q=*s=='\'',bq=*s=='`',qm=s[q]=='"';
	char *tok=get_token(s);
	switch (infer_type(tok)) {
	case CELL:
		if (bq)
			obj=to_splice(tok+1);
		else
			obj=to_list(tok);
		break;
	case SYMBOL:
		TRY // lets "else if" statements follow
		CATCH_CONST(NIL)
		CATCH_CONST(T)
		CATCH_CONST(QUOTE)
		CATCH_CONST(PROGN)
		CATCH_CONST(COND)
		CATCH_CONST(VARIADIC)
		CATCH_CONST(GO)
		CATCH_CONST(PI)
		// Don't catch ARGV
		else if (tok[0]=='@'&&!tok[1]) // CATCH_CONST(@)
			obj=RECURSE;
		else
			obj=new_obj(SYMBOL,(long)tok,qm);
		return q?quote(obj):obj;
	case INTEGER:
		obj=new_obj(INTEGER,atol(tok),0);
		break;
	case DOUBLE:
		obj=new_dobj(strtod(tok,NULL));
		break;
	default:
		obj=&ERROR_OBJ;
	}
	free(tok);
	if (q)
		obj=quote(obj);
	DEBUG(fprintf(stderr,"Read: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	return obj;
}
obj_t *to_splice(char *str)
{	// Expects list string after parenthesis
	str=ltrim(str);
	bool u=*str==':';
	str+=u;
	bool s=*str=='\\';
	str+=s;
	bool q=*str=='\'';
	str+=q;
	bool bq=*str=='`';
	str+=bq;
	char *tok=get_token(str);
	if (!tok)
		return NIL;
	int len=strlen(tok);
	obj_t *f=s?&append_fun:&cons_fun,*o;
	if (infer_type(tok)==CELL&&!u&&!s) {
		o=to_splice(tok+1);
		u=true;
	} else
		o=to_obj(tok);
	if (q)
		o=quote(o);
	free(tok);
	if (!u&&!s)
		o=quote(o);
	// (f o (@ (+ str len 1))))
	return cons(f,cons(o,cons(to_splice(str+len),NIL)));
}

