#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "stack.h"
#include "dict.h"
int main(int argc,char **argv)
{
	char *str1=strcpy(calloc(8,1),"x");
	char *str2=strcpy(calloc(8,1),"y");
	push(new_obj(SYMBOL,(long)str1,0));
	push(new_obj(SYMBOL,(long)str2,0));
	s_cons();
	dup();
	s_car();
	over();
	s_cdr();
	push(NIL);
	s_cons();
	s_cons();
	push(NIL);
	s_cons();
	s_cons();
	s_print();
	drop();
	terpri();
	return 0;
}
