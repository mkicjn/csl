#ifndef	RPN_H
#define RPN_H
#include "lisp.h"
obj_t *rpn(obj_t *form)
{
	if (form->type!=CELL)
		return cons(form,NIL);
	push(NULL);
	for (obj_t *o=cdr(form);o!=NIL;o=cdr(o))
		push(rpn(car(o)));
	push(rpn(car(form)));
	while (stackitem(1))
		s_nconc();
	obj_t *r=pop();
	pop(); // Drop NULL
//	r->refs-=r->refs>0;
//	dec_rc(form);
	return r;
}
#endif
