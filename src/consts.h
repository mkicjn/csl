#ifndef CONSTS_H
#define CONSTS_H
#include "types.h"
#define CONSTANT(x) \
{ \
	.type=SYMBOL, \
	.car=(long)#x, \
	.cdr=0, \
	.refs=-1 \
}
#define NEW_CONSTANT(x) \
obj_t x##_OBJ=CONSTANT(x); \
obj_t *x=&x##_OBJ;
// Directly available
extern obj_t NIL_OBJ;
extern obj_t *NIL;
extern obj_t *T;
extern obj_t *RECURSE;
extern obj_t *QUOTE;
extern obj_t *PROGN;
extern obj_t *COND;
extern obj_t *VARIADIC;
extern obj_t *ARGV;
extern obj_t *GO;
// Normally unavailable
extern obj_t ERROR_OBJ;
extern obj_t ARGS;
extern obj_t CALL;
extern obj_t DROP;
extern obj_t COND_BEGIN;
extern obj_t COND_DO;
extern obj_t COND_DONE;
extern obj_t COND_END;
extern obj_t *DICT;
// Type symbols
extern obj_t *type_objs[5];
// Not actually constant
extern obj_t *ENV;
#endif
