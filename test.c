#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "stack.h"
#include "reader.h"
#include "dict.h"
#include "rpn.h"
static void push_symbol(const char *str)
{
	int len=strlen(str)+1;
	push(new_obj(SYMBOL,(long)strcpy(calloc(len,1),str),len));
}
int main(int argc,char **argv)
{
	push(&ARGS);
	push_symbol("x");
	push_symbol("y");
	push_symbol("z");
	s_list();
	s_print();
	drop();
	terpri();
	l_exit();
}
