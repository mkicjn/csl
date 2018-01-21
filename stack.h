#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 1024
#include "lisp.h"
static obj_t *lisp_stack[STACK_SIZE];
static int stack_index=0;
void push(obj_t *obj)
{
	lisp_stack[stack_index++]=obj;
}
obj_t *pop()
{
	return lisp_stack[--stack_index];
}
void swap()
{
	obj_t *o=lisp_stack[stack_index-2];
	lisp_stack[stack_index-2]=lisp_stack[stack_index-1];
	lisp_stack[stack_index-1]=o;
}
void drop()
{
	dec_rc(pop());
}
void pick(int n)
{
	push(lisp_stack[stack_index-1-n]);
}
void dup()
{
	push(lisp_stack[stack_index-1]);
}
void over()
{
	push(lisp_stack[stack_index-2]);
}
#endif
