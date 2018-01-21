#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "stack.h"
#include "lisp.h"
void s_car() {
	obj_t *a=pop();
	push(car(a));
	dec_rc(a);
}
void s_cdr() {
	obj_t *a=pop();
	push(cdr(a));
	dec_rc(a);
}
void s_cons() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(cons(a,b));
	dec_rc(a);
	dec_rc(b);
}
void s_print() {
	obj_t *a=pop();
	push(print(a));
	dec_rc(a);
}
void s_terpri() {
	obj_t *a=pop();
	push(terpri(a));
	dec_rc(a);
}
void s_eq() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(eq(a,b));
	dec_rc(a);
	dec_rc(b);
}
#endif
