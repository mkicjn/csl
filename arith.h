#ifndef ARITH_H
#define ARITH_H
#include "consts.h"
#include "memman.h"
#include "types.h"
static bool is_num(obj_t *);
core(+,2) add(obj_t *,obj_t *);
core(-,2) sub(obj_t *,obj_t *);
core(*,2) mult(obj_t *,obj_t *);
core(/,2) divd(obj_t *,obj_t *);
core(>,2) gt(obj_t *,obj_t *);
core(<,2) lt(obj_t *,obj_t *);
core(=,2) eqn(obj_t *,obj_t *);
core(RANDOM,1) lrand(obj_t *);
core(%,2) lmod(obj_t *,obj_t *);
#endif
