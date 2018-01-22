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
char *captok(char *s)
{
	for (;*s&&*s==' '||*s=='\t';s++); // Skip whitespace
	register int c=0;
	for (;s[c]&&s[c]!=' '&&s[c]!='\t';c++); // Skip non-whitespace
	char *t=calloc(c+1,1);
	return memcpy(t,s,c);
}
#endif
