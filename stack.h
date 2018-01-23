#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 1024
#include "lisp.h"
static obj_t *lisp_stack[STACK_SIZE];
static int stack_index=0;
obj_t *stackitem(int n)
{
	return lisp_stack[stack_index-1-n];
}
void push(obj_t *obj)
{
	inc_rc(obj);
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
extern inline void drop()
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
