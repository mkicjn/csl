#ifndef ARITH_H
#define ARITH_H
#include "lisp.h"
static bool is_num(obj_t *obj)
{
	return obj->type==INTEGER&&obj->type==DOUBLE;
}
core(+,2) add(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER)
		return new_obj(INTEGER,a->car+b->car,0);
	double n1,n2;
	n1=a->type==INTEGER?(double)a->car:((dobj_t *)a)->car;
	n2=b->type==INTEGER?(double)b->car:((dobj_t *)b)->car;
	return new_dobj(n1+n2);
}
core(-,2) sub(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER)
		return new_obj(INTEGER,a->car-b->car,0);
	double n1=a->type==INTEGER?(double)a->car:((dobj_t *)a)->car;
	double n2=b->type==INTEGER?(double)b->car:((dobj_t *)b)->car;
	return new_dobj(n1-n2);
}
core(*,2) mult(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER)
		return new_obj(INTEGER,a->car*b->car,0);
	double n1,n2;
	n1=a->type==INTEGER?(double)a->car:((dobj_t *)a)->car;
	n2=b->type==INTEGER?(double)b->car:((dobj_t *)b)->car;
	return new_dobj(n1*n2);
}
core(/,2) divd(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER&&a->car%b->car==0)
		return new_obj(INTEGER,a->car/b->car,0);
	double n1=a->type==INTEGER?(double)a->car:((dobj_t *)a)->car;
	double n2=b->type==INTEGER?(double)b->car:((dobj_t *)b)->car;
	return new_dobj(n1/n2);
}
#endif
