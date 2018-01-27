#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "stack.h"
#include "reader.h"
#include "dict.h"
#include "rpn.h"
static void push_sym(const char *str)
{
	int len=strlen(str)+1;
	push(new_obj(SYMBOL,(long)strcpy(calloc(len,1),str),len));
}
int main(int argc,char **argv)
{
	if (argc>1) {
		push(NIL);
		push_sym(argv[1]);
		s_load();
		s_lambda();
		s_funcall();
		l_exit();
	}
	push(NIL);
	push(lread(200));
	s_lambda();
	s_funcall();
	s_print();
	terpri();
	l_exit();
}
