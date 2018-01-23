#ifndef	RPN_H
#define RPN_H
#include "lisp.h"
#include "stack.h"
obj_t *rpnh(obj_t *);
obj_t *rpn(obj_t *form)
{
	obj_t *r=rpnh(form);
	dec_rc(form);
	return r;
}
obj_t *rpnh(obj_t *form)
{
	if (form->type!=CELL)
		return cons(form,NIL);
	push(NULL);
	for (obj_t *o=cdr(form);o!=NIL;o=cdr(o))
		push(rpnh(car(o)));
	push(rpnh(car(form)));
	while (stackitem(1))
		s_nconc();
	obj_t *r=pop();
	pop(); // Drop NULL
	r->refs--;
	return r;
}
#endif
