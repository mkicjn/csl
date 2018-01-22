#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "stack.h"
#include "dict.h"
static void push_symbol(const char *str)
{
	int len=strlen(str)+1;
	push(new_obj(SYMBOL,(long)strcpy(calloc(len,1),str),len));
}
int main(int argc,char **argv)
{
	/*
	push_symbol("x");
	push_symbol("y");
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
	push_symbol("x");
	push_symbol("y");
	push(NIL);
	s_cons();
	s_cons();
	push_symbol("a");
	s_rplacd();
	s_print();
	drop();
	terpri();
	return 0;
}
