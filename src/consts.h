#ifndef CONSTS_H
#define CONSTS_H
#include "types.h"
#define CONSTANT(x) {	\
	.type=SYMBOL,	\
	.car=(long)#x,	\
	.cdr=0,		\
	.refs=-1	\
}
extern obj_t *NIL;
extern obj_t *T;
extern obj_t *SELF;
extern obj_t *QUOTE;
extern obj_t *PROGN;
extern obj_t *COND;
extern obj_t ERROR_OBJ;
extern obj_t ARGS;
extern obj_t CALL;
extern obj_t DROP;
extern obj_t COND_DO;
extern obj_t COND_END;
extern obj_t *DICT;
extern obj_t *ENV;
extern obj_t *type_objs[5];
#endif
