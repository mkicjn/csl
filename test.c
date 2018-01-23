#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisp.h"
#include "reader.h"
#include "stack.h"
#include "dict.h"
static void push_symbol(const char *str)
{
	int len=strlen(str)+1;
	push(new_obj(SYMBOL,(long)strcpy(calloc(len,1),str),len));
}
int main(int argc,char **argv)
{
	char str[200];
	fgets(str,200,stdin);
	str[strlen(str)-1]='\0';
	puts(str);
	char *str2=get_token(str);
	printf("%s - %s\n",str2,types[infer_type(str2)]);
	free(str2);
	return 0;
}
