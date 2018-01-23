#ifndef STACK_H
#define STACK_H
#define STACK_SIZE 1024
static void *lisp_stack[STACK_SIZE];
static int stack_index=0;
void *stackitem(int n)
{
	return lisp_stack[stack_index-1-n];
}
void push(void *obj)
{
	inc_rc(obj);
	lisp_stack[stack_index++]=obj;
}
void *pop()
{
	return lisp_stack[--stack_index];
}
void swap()
{
	void *o=lisp_stack[stack_index-2];
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
