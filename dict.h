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
	push(cons(b,a));
	dec_rc(b);
	dec_rc(a);
}
void s_print() {
	obj_t *a=pop();
	push(print(a));
	dec_rc(a);
}
void s_terpri() {
	push(terpri());
}
void s_eq() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(eq(b,a));
	dec_rc(b);
	dec_rc(a);
}
void s_set() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(set(b,a));
	dec_rc(b);
	dec_rc(a);
}
#endif
