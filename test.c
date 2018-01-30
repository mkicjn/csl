#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "stack.h"
#include "reader.h"
#include "dict.h"
#include "rpn.h"
#include "arith.h"
static void push_sym(const char *str)
{
	int len=strlen(str)+1;
	push(new_obj(SYMBOL,(long)strcpy(calloc(len,1),str),len));
}
int main(int argc,char **argv)
{
	if (argc>1) {
		for (int i=1;i<argc;i++) {
			push(NIL);
			push_sym(argv[i]);
			s_load();
			s_eval();
		}
		l_exit();
	}
	for (;;) {
		push(lread(200));
		s_eval();
		terpri();
		s_print();
		terpri();
		drop();
	}
}
