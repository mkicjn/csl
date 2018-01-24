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
	push(rpn(lread(200)));
	s_print();
	drop();
	terpri();
	l_exit();
}
