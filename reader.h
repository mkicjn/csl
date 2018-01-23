#ifndef READER_H
#define READER_H
#include <stdlib.h>
#include "lisp.h"
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
	bool quote=*s=='\'';
	if (quote)
		s++;
	if (*s=='(')
		return valid_list(s)?CELL:ERROR;
	if (*s=='-')
		s++;
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
	for (;s[c]&&s[c]!=' '&&s[c]!='\t';c++); // Count characters
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
	return memcpy(calloc(c+1,1),s,c+1);
}
char *get_token(char *s)
{
	if (!*s)
		return NULL;
	for (;*s&&*s==' '||*s=='\t';s++); // Skip whitespace
	if (*s=='\'')
		s++;
	if (*s=='(')
		return get_list(s);
	return get_word(s);
}
#endif
