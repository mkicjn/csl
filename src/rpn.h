#ifndef RPN_H
#define RPN_H
#include "core.h"
#include "consts.h"
#include "dict.h"
#include "types.h"
obj_t *t_progn(obj_t *);
obj_t *t_cond(obj_t *);
obj_t *rpn(obj_t *);
obj_t *rpnd(obj_t *);
obj_t *t_progn(obj_t *);
obj_t *t_cond(obj_t *);
#endif
