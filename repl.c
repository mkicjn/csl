#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	srand(time(NULL));
	if (argc>1) {
		for (int i=1;i<argc;i++) {
			push(NIL);
			push_sym(argv[i]);
			s_load();
			s_eval();
		}
		l_exit();
	}
	char input[200];
	for (;;) {
		input[0]=0;
		fgets(input,200,stdin);
		if (!input[0]) {
			printf("(EXIT)\n");
			l_exit();
		}
		push(to_obj(input));
		s_eval();
		printf("\n=> ");
		s_print();
		terpri();
		dec_rc(pop());
	}
}
