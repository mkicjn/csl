#include "stack.h"
static obj_t *l_stack[STACK_SIZE];
static int s_index=0; // l_stack[s_index] should be top stack item
// Stack functions
obj_t *stackitem(int n)
{
	return l_stack[s_index-n];
}
void push(obj_t *obj)
{
	inc_rc(obj);
	l_stack[++s_index]=obj;
}
obj_t *pop()
{
	return l_stack[s_index--];
}
void swap()
{
	obj_t *o=l_stack[s_index-1];
	l_stack[s_index-1]=l_stack[s_index];
	l_stack[s_index]=o;
}
void pick(int n)
{
	push(l_stack[s_index-n]);
}
void dupe()
{
	push(l_stack[s_index]);
}
void over()
{
	push(l_stack[s_index-1]);
}
void nip()
{
	dec_rc(l_stack[s_index-1]);
	l_stack[s_index-1]=l_stack[s_index];
	s_index--;
}
void ndrop(int n) // For use in bind_args
{	// Does not decrement reference counters!
	s_index-=n;
}
