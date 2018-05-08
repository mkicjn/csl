#ifndef ARITH_H
#define ARITH_H
#include <math.h>
#include "consts.h"
#include "memman.h"
#include "types.h"
#define CMATH(lname,cfunc) \
/**/core(lname,1) l##cfunc(obj_t *n) \
{ \
	if (!is_num(n)) \
		return &ERROR_OBJ; \
	return new_dobj(cfunc(dub(n))); \
}

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
core(EXPT,2) expt(obj_t *,obj_t *);
core(SQRT,1) lsqrt(obj_t *);
core(EXP,1) lexp(obj_t *);
core(LOG,1) llog(obj_t *);
core(SIN,1) lsin(obj_t *);
core(COS,1) lcos(obj_t *);
core(TAN,1) ltan(obj_t *);
#endif
