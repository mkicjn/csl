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
#endif
