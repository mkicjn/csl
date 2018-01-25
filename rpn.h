#ifndef	RPN_H
#define RPN_H
#include "lisp.h"
#include "stack.h"
obj_t *rpn(obj_t *form)
{
	if (form->type!=CELL)
		return cons(form,NIL);
	if (car(form)==QUOTE)
		return form;
	push(NULL);
	push(cons(&ARGS,NIL));
	for (obj_t *o=cdr(form);o!=NIL;o=cdr(o))
		push(rpn(car(o)));
	push(rpn(car(form)));
	push(cons(&CALL,NIL));
	while (stackitem(1))
		s_nconc();
	obj_t *r=pop();
	pop(); // Drop NULL
	r->refs--;
	return r;
}
obj_t *rpnd(obj_t *form)
{
	obj_t *r=rpn(form);
	dec_rc(form);
	return r;
}
#endif
