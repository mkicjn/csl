#ifndef READER_H
#define READER_H
#include <stdlib.h>
#include "lisp.h"
char *ltrim(char *s)
{
	for (;*s==' '||*s=='\n'||*s=='\t';s++);
	return s;
}
bool valid_list(char *s)
{
	int p=0;
	for (;*s;s++) {
		if (*s=='(')
			p++;
		else if (*s==')')
			p--;
	}
	return p==0;
}
type_t infer_type(char *s)
{
	if (!s)
		return ERROR;
	s+=*s=='\''; // Skip apostrophe if quoted
	if (*s=='(')
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
	for (;s[c]&&s[c]!=' '&&s[c]!='\t'&&s[c]!='\n'&&s[c]!=')';c++); // Count characters
	return memcpy(calloc(c+1,1),s,c);
}
char *get_list(char *s)
{
	register int c=0,p=0;
	for (;s[c];c++) { // Count parentheses
		if (s[c]=='(')
			p++;
		else if (s[c]==')') {
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
	if (*s=='\'')
		s++;
	if (*s=='(')
		return get_list(s);
	return get_word(s);
}
obj_t *quote(obj_t *obj)
{
	if (obj==NIL||obj==T||obj==SELF)
		return obj;
	return cons(QUOTE,cons(obj,NIL));
}
obj_t *to_obj(char *);
extern void s_cons();
obj_t *to_list(char *s)
{
	push(NULL); // Marker for front of list
	bool dot=false;
	if (*s=='\'')
		s++;
	s++;
	while (*s&&*(s=ltrim(s))!=')') {
		bool q=*s=='\'';
		char *tok=get_token(s);
		if (!tok)
			break;
		int len=strlen(tok);
		if (tok[0]=='.'&&!tok[1]) {
			dot=true;
			free(tok);
			s++;
			continue;
		}
		push(q?quote(to_obj(tok)):to_obj(tok));
		free(tok);
		if (dot)
			break;
		s+=len+q;
	}
	if (!dot)
		push(NIL);
	while (stackitem(1))
		s_cons();
	obj_t *list=pop();
	pop(); // Get rid of NULL on stack
	list->refs--;
	return list;
}
obj_t *to_obj(char *s)
{
	obj_t *obj;
	bool q=*s=='\'';
	char *tok=get_token(s);
	switch (infer_type(tok)) {
	case CELL:
		obj=to_list(tok);
		break;
	case SYMBOL:
		if (!strcasecmp(tok,"NIL"))
			obj=NIL;
		else if (!strcasecmp(tok,"T"))
			obj=T;
		else if (!strcasecmp(tok,"@"))
			obj=SELF;
		else if (!strcasecmp(tok,"QUOTE"))
			obj=QUOTE;
		else if (!strcasecmp(tok,"PROGN"))
			obj=PROGN;
		else {
			obj=new_obj(SYMBOL,(long)tok,strlen(tok));
			return q?quote(obj):obj;
		}
		break;
	case INTEGER:
		obj=new_obj(INTEGER,atol(tok),0);
		break;
	case DOUBLE:
		obj=new_dobj(strtod(tok,NULL));
		break;
	default:
		obj=NIL;
	}
	free(tok);
	return q?quote(obj):obj;
}
#endif
