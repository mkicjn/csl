#ifndef MEMMAN_H
#define MEMMAN_H
#include <stdlib.h>
#include "types.h"
#define new(x) malloc(sizeof(x));
obj_t *new_obj(type_t,long,long);
obj_t *new_dobj(double);
void dec_rc(obj_t *);
void destroy(obj_t *);
void destroy_func(obj_t *);
void inc_rc(obj_t *);
void dec_rc(obj_t *);
#endif
