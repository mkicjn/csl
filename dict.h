#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "stack.h"
#define FUNCTION_OBJ(x) {.type=FUNCTION,.car=(long)x,.cdr=-1,.refs=-1}
#define CONS_OBJ(x,y) {.type=CELL,.car=(long)x,.cdr=(long)y,.refs=-1}
#include "lisp.h"
void s_car() {
	obj_t *a=pop();
	push(car(a));
	dec_rc(a);
}
obj_t car_sym=CONSTANT(CAR);
obj_t car_fun=FUNCTION_OBJ(&s_car);
obj_t car_def=CONS_OBJ(&car_sym,&car_fun);
obj_t car_dcell=CONS_OBJ(&car_def,&NIL_OBJ);
void s_cdr() {
	obj_t *a=pop();
	push(cdr(a));
	dec_rc(a);
}
obj_t cdr_sym=CONSTANT(CDR);
obj_t cdr_fun=FUNCTION_OBJ(&s_cdr);
obj_t cdr_def=CONS_OBJ(&cdr_sym,&cdr_fun);
obj_t cdr_dcell=CONS_OBJ(&cdr_def,&car_dcell);
void s_cons() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(cons(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t cons_sym=CONSTANT(CONS);
obj_t cons_fun=FUNCTION_OBJ(&s_cons);
obj_t cons_def=CONS_OBJ(&cons_sym,&cons_fun);
obj_t cons_dcell=CONS_OBJ(&cons_def,&cdr_dcell);
void s_print() {
	obj_t *a=pop();
	push(print(a));
	dec_rc(a);
}
obj_t print_sym=CONSTANT(PRINT);
obj_t print_fun=FUNCTION_OBJ(&s_print);
obj_t print_def=CONS_OBJ(&print_sym,&print_fun);
obj_t print_dcell=CONS_OBJ(&print_def,&cons_dcell);
void s_terpri() {
	push(terpri());
}
obj_t terpri_sym=CONSTANT(TERPRI);
obj_t terpri_fun=FUNCTION_OBJ(&s_terpri);
obj_t terpri_def=CONS_OBJ(&terpri_sym,&terpri_fun);
obj_t terpri_dcell=CONS_OBJ(&terpri_def,&print_dcell);
void s_eq() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(eq(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t eq_sym=CONSTANT(EQ);
obj_t eq_fun=FUNCTION_OBJ(&s_eq);
obj_t eq_def=CONS_OBJ(&eq_sym,&eq_fun);
obj_t eq_dcell=CONS_OBJ(&eq_def,&terpri_dcell);
void s_set() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(set(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t set_sym=CONSTANT(SET);
obj_t set_fun=FUNCTION_OBJ(&s_set);
obj_t set_def=CONS_OBJ(&set_sym,&set_fun);
obj_t set_dcell=CONS_OBJ(&set_def,&eq_dcell);
void s_rplaca() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(rplaca(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t rplaca_sym=CONSTANT(RPLACA);
obj_t rplaca_fun=FUNCTION_OBJ(&s_rplaca);
obj_t rplaca_def=CONS_OBJ(&rplaca_sym,&rplaca_fun);
obj_t rplaca_dcell=CONS_OBJ(&rplaca_def,&set_dcell);
void s_rplacd() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(rplacd(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t rplacd_sym=CONSTANT(RPLACD);
obj_t rplacd_fun=FUNCTION_OBJ(&s_rplacd);
obj_t rplacd_def=CONS_OBJ(&rplacd_sym,&rplacd_fun);
obj_t rplacd_dcell=CONS_OBJ(&rplacd_def,&rplaca_dcell);
void s_read() {
	obj_t *a=pop();
	push(oread(a));
	dec_rc(a);
}
obj_t oread_sym=CONSTANT(READ);
obj_t oread_fun=FUNCTION_OBJ(&s_read);
obj_t oread_def=CONS_OBJ(&oread_sym,&oread_fun);
obj_t oread_dcell=CONS_OBJ(&oread_def,&rplacd_dcell);
void s_atom() {
	obj_t *a=pop();
	push(atom(a));
	dec_rc(a);
}
obj_t atom_sym=CONSTANT(ATOM);
obj_t atom_fun=FUNCTION_OBJ(&s_atom);
obj_t atom_def=CONS_OBJ(&atom_sym,&atom_fun);
obj_t atom_dcell=CONS_OBJ(&atom_def,&oread_dcell);
void s_null() {
	obj_t *a=pop();
	push(null(a));
	dec_rc(a);
}
obj_t null_sym=CONSTANT(NULL);
obj_t null_fun=FUNCTION_OBJ(&s_null);
obj_t null_def=CONS_OBJ(&null_sym,&null_fun);
obj_t null_dcell=CONS_OBJ(&null_def,&atom_dcell);
void s_nconc() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(nconc(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t nconc_sym=CONSTANT(NCONC);
obj_t nconc_fun=FUNCTION_OBJ(&s_nconc);
obj_t nconc_def=CONS_OBJ(&nconc_sym,&nconc_fun);
obj_t nconc_dcell=CONS_OBJ(&nconc_def,&null_dcell);
void s_copy() {
	obj_t *a=pop();
	push(copy(a));
	dec_rc(a);
}
obj_t copy_sym=CONSTANT(COPY);
obj_t copy_fun=FUNCTION_OBJ(&s_copy);
obj_t copy_def=CONS_OBJ(&copy_sym,&copy_fun);
obj_t copy_dcell=CONS_OBJ(&copy_def,&nconc_dcell);
void s_append() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(append(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t append_sym=CONSTANT(APPEND);
obj_t append_fun=FUNCTION_OBJ(&s_append);
obj_t append_def=CONS_OBJ(&append_sym,&append_fun);
obj_t append_dcell=CONS_OBJ(&append_def,&copy_dcell);
void s_assoc() {
	obj_t *a=pop();
	obj_t *b=pop();
	push(assoc(b,a));
	dec_rc(b);
	dec_rc(a);
}
obj_t assoc_sym=CONSTANT(ASSOC);
obj_t assoc_fun=FUNCTION_OBJ(&s_assoc);
obj_t assoc_def=CONS_OBJ(&assoc_sym,&assoc_fun);
obj_t assoc_dcell=CONS_OBJ(&assoc_def,&append_dcell);
const obj_t *DICT=&assoc_dcell;
#endif
