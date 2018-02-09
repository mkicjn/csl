#ifndef DICTIONARY_H
#define DICTIONARY_H
#include "stack.h"
#define FUNCTION_OBJ(x) {.type=FUNCTION,.car=(long)x,.cdr=-1,.refs=-1}
#define CONS_OBJ(x,y) {.type=CELL,.car=(long)x,.cdr=(long)y,.refs=-1}
#include "core.h"
void s_car();
extern obj_t car_fun;
void s_cdr();
extern obj_t cdr_fun;
void s_cons();
extern obj_t cons_fun;
void s_print();
extern obj_t print_fun;
void s_terpri();
extern obj_t terpri_fun;
void s_eq();
extern obj_t eq_fun;
void s_set();
extern obj_t set_fun;
void s_rplaca();
extern obj_t rplaca_fun;
void s_rplacd();
extern obj_t rplacd_fun;
void s_oread();
extern obj_t oread_fun;
void s_atom();
extern obj_t atom_fun;
void s_null();
extern obj_t null_fun;
void s_nconc();
extern obj_t nconc_fun;
void s_copy();
extern obj_t copy_fun;
void s_append();
extern obj_t append_fun;
void s_assoc();
extern obj_t assoc_fun;
void s_declare();
extern obj_t declare_fun;
void s_define();
extern obj_t define_fun;
void s_symval();
extern obj_t symval_fun;
void s_l_exit();
extern obj_t l_exit_fun;
void s_list();
extern obj_t list_fun;
void s_l_length();
extern obj_t l_length_fun;
void s_lambda();
extern obj_t lambda_fun;
void s_see();
extern obj_t see_fun;
void s_funcall();
extern obj_t funcall_fun;
void s_load();
extern obj_t load_fun;
void s_eval();
extern obj_t eval_fun;
void s_type();
extern obj_t type_fun;
#include "arith.h"
void s_add();
extern obj_t add_fun;
void s_sub();
extern obj_t sub_fun;
void s_mult();
extern obj_t mult_fun;
void s_divd();
extern obj_t divd_fun;
void s_gt();
extern obj_t gt_fun;
void s_lt();
extern obj_t lt_fun;
void s_eqn();
extern obj_t eqn_fun;
void s_lrand();
extern obj_t lrand_fun;
void s_lmod();
extern obj_t lmod_fun;
extern obj_t *DICT;
#endif
