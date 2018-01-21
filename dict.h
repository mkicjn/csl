#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "stack.h"
#include "lisp.h"
void s_car() {push(car(pop()));}
void s_cdr() {push(cdr(pop()));}
void s_cons() {push(cons(pop(),pop()));}
void s_print() {push(print(pop()));}
void s_terpri() {push(terpri());}
#endif
