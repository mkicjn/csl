#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "stack.h"
#include "dict.h"
int main(int argc,char **argv)
{
	/*
	push(new_obj(SYMBOL,(long)strcpy(calloc(8,1),"x"),8));
	push(new_obj(SYMBOL,(long)strcpy(calloc(8,1),"y"),8));
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
	*/
	/*
	push(new_obj(INTEGER,1,0));
	dup();
	s_eq();
	s_print();
	drop();
	terpri();
	*/
	push(new_obj(SYMBOL,(long)strcpy(calloc(8,1),"x"),8));
	dup();
	push(new_obj(SYMBOL,(long)strcpy(calloc(8,1),"y"),8));
	s_set();
	drop();
	s_print();
	drop();
	terpri();
	return 0;
}
