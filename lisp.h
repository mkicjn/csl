#ifndef LISP_H
#define LISP_H
#define CASE_INSENSITIVE
#include <stdlib.h>
// Type definitions
typedef enum {false,true} bool;
typedef enum {CELL,SYMBOL,INTEGER,FUNCTION,DOUBLE} type_t;
typedef struct {
	type_t type;
	long car,cdr;
	int refs;
} obj_t;
// Memory functions
#define new(x) malloc(sizeof(x));
obj_t *new_obj(type_t type,long car,long cdr)
{
	obj_t *obj=new(obj_t);
	obj->type=type;
	obj->car=car;
	obj->cdr=cdr;
	obj->refs=0;
}
obj_t *dec_rc(obj_t *);
void destroy(obj_t *obj)
{
	switch (obj->type) {
	case SYMBOL:
	case FUNCTION:
		free((void *)obj->car);
	case DOUBLE:
	case INTEGER:
		free(obj);
		break;
	case CELL:
		dec_rc((obj_t *)obj->car);
		dec_rc((obj_t *)obj->cdr);
		free(obj);
	}
}
void rcdestroy(obj_t *obj)
{
	if (obj->refs==0)
		destroy(obj);
}
obj_t *inc_rc(obj_t *obj)
{
	if (0xff>(long)obj)
		return obj;
	if (obj->refs>=0)
		obj->refs++;
	return obj;
}
obj_t *dec_rc(obj_t *obj)
{
	if (0xff>(long)obj)
		return obj;
	if (obj->refs>0)
		obj->refs--;
	if (obj->refs==0)
		destroy(obj);
	return obj;
}
// Constants
#define CONSTANT(x) {	\
	.type=SYMBOL,	\
	.car=(long)#x,	\
	.cdr=0,		\
	.refs=-1	\
}
obj_t NIL_OBJ=CONSTANT(NIL);
obj_t *NIL=&NIL_OBJ;
obj_t T_OBJ=CONSTANT(T);
obj_t *T=&T_OBJ;
obj_t SELF_OBJ=CONSTANT(@);
obj_t *SELF=&SELF_OBJ;
// LISP core functions
#define core(name,argc) obj_t * // Info for dictionary code generator
core(CAR,1) car(obj_t *obj)
{
	if (obj->type==CELL)
		return (obj_t *)obj->car;
	return NIL;
}
core(CDR,1) cdr(obj_t *obj)
{
	if (obj->type==CELL)
		return (obj_t *)obj->cdr;
	return NIL;
}
core(CONS,2) cons(obj_t *obj2,obj_t *obj1)
{
	inc_rc(obj1);
	inc_rc(obj2);
	return new_obj(CELL,(long)obj1,(long)obj2);
}
void print_cell(obj_t *);
core(PRINT,1) print(obj_t *obj)
{
	switch (obj->type) {
	case CELL:
		print_cell(obj);
		break;
	case SYMBOL:
		printf("%s",(char *)obj->car);
		break;
	case INTEGER:
		printf("%ld",obj->car);
		break;
	case FUNCTION:
		printf("{FUNCTION 0x%x}",obj);
		break;
	case DOUBLE:
		printf("%f",(double)obj->car);
		break;
	default:
		printf("{ERROR}");
	}
	return obj;
}
void print_cell(obj_t *obj)
{
	putchar('(');
	obj_t *o=obj;
	while (o!=NIL) {
		if (o->type!=CELL) {
			fputs(". ",stdout);
			print(o);
			putchar(')');
			return;
		}
		print(car(o));
		if ((obj_t *)o->cdr!=NIL)
			putchar(' ');
		o=(obj_t *)o->cdr;
	}
	putchar(')');
}
core(TERPRI,0) terpri() {
	putchar('\n');
	return NIL;
}
core(EQ,2) eq(obj_t *obj1,obj_t *obj2)
{
	if (obj1==obj2)
		return T;
	if (obj1->type!=obj2->type)
		return NIL;
	switch (obj1->type) {
	case CELL:
		return NIL;
	case SYMBOL:
		return strcasecmp((char *)obj1->car,(char *)obj2->car)?NIL:T;
	case INTEGER:
	case DOUBLE:
		return obj1->car==obj2->car ? T : NIL;
	case FUNCTION:
		return NIL;
	}
}
#endif
