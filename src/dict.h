#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "stack.h"
#define FUNCTION_OBJ(x) {.type=FUNCTION,.car=(long)x,.cdr=-1,.refs=-1}
#define CONS_OBJ(x,y) {.type=CELL,.car=(long)x,.cdr=(long)y,.refs=-1}
#include "core.h"
void s_car();
void s_cdr();
void s_cons();
void s_print();
void s_terpri();
void s_eq();
void s_set();
void s_rplaca();
void s_rplacd();
void s_oread();
void s_atom();
void s_null();
void s_nconc();
void s_copy();
void s_append();
void s_assoc();
void s_declare();
void s_define();
void s_symval();
void s_l_exit();
void s_list();
void s_l_length();
void s_lambda();
void s_see();
void s_funcall();
void s_load();
void s_eval();
#include "arith.h"
void s_add();
void s_sub();
void s_mult();
void s_divd();
void s_gt();
void s_lt();
void s_eqn();
void s_lrand();
void s_lmod();
extern obj_t *DICT;
#endif
