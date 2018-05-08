#include "arith.h"
static bool is_num(obj_t *obj)
{
	return obj->type==INTEGER||obj->type==DOUBLE;
}
static double dub(obj_t *n)
{
	double d;
	switch (n->type) {
	case INTEGER:
		return d=(double)n->car;
	case DOUBLE:
		return ((dobj_t *)n)->car;
	default:
		return 0;
	}
}
core(+,2) add(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER)
		return new_obj(INTEGER,a->car+b->car,0);
	double n1,n2;
	n1=a->type==INTEGER?(double)a->car:dub(a);
	n2=b->type==INTEGER?(double)b->car:dub(b);
	return new_dobj(n1+n2);
}
core(-,2) sub(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER)
		return new_obj(INTEGER,a->car-b->car,0);
	double n1=a->type==INTEGER?(double)a->car:dub(a);
	double n2=b->type==INTEGER?(double)b->car:dub(b);
	return new_dobj(n1-n2);
}
core(*,2) mult(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER)
		return new_obj(INTEGER,a->car*b->car,0);
	double n1,n2;
	n1=a->type==INTEGER?(double)a->car:dub(a);
	n2=b->type==INTEGER?(double)b->car:dub(b);
	return new_dobj(n1*n2);
}
core(/,2) divd(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type==INTEGER&&b->type==INTEGER&&a->car%b->car==0)
		return new_obj(INTEGER,a->car/b->car,0);
	double n1=a->type==INTEGER?(double)a->car:dub(a);
	double n2=b->type==INTEGER?(double)b->car:dub(b);
	return new_dobj(n1/n2);
}
core(>,2) gt(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	double n1=a->type==INTEGER?(double)a->car:dub(a);
	double n2=b->type==INTEGER?(double)b->car:dub(b);
	return n1>n2?T:NIL;
}
core(<,2) lt(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	double n1=a->type==INTEGER?(double)a->car:dub(a);
	double n2=b->type==INTEGER?(double)b->car:dub(b);
	return n1<n2?T:NIL;
}
core(=,2) eqn(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	double n1=a->type==INTEGER?(double)a->car:dub(a);
	double n2=b->type==INTEGER?(double)b->car:dub(b);
	return n1==n2?T:NIL;
}
core(RANDOM,1) lrand(obj_t *obj)
{
	if (obj->type!=INTEGER)
		return &ERROR_OBJ;
	return new_obj(INTEGER,rand()%obj->car,0);
}
core(%,2) lmod(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type!=INTEGER||b->type!=INTEGER)
		return new_dobj(fmod(dub(a),dub(b)));
	return new_obj(INTEGER,a->car%b->car,0);
}
core(EXPT,2) expt(obj_t *a,obj_t *b)
{
	if (!is_num(a)||!is_num(b))
		return &ERROR_OBJ;
	if (a->type!=INTEGER||b->type!=INTEGER)
		return new_dobj(pow(dub(a),dub(b)));
	return new_obj(INTEGER,floor(pow(a->car,b->car)),0);
}
CMATH(SQRT,sqrt);
CMATH(LOG,log);
CMATH(EXP,exp);
CMATH(SIN,sin);
CMATH(COS,cos);
CMATH(TAN,tan);
