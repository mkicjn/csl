#include "memman.h"
obj_t *new_obj(type_t type,long car,long cdr)
{
	obj_t *obj=new(obj_t);
	obj->type=type;
	obj->car=car;
	obj->cdr=cdr;
	obj->refs=0;
	DEBUG(fprintf(stderr,"New object: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	return obj;
}
obj_t *new_dobj(double car)
{
	// This function exists to circumvent implicit typecasting
	obj_t *obj=new(obj_t);
	obj->type=DOUBLE;
	((dobj_t *)obj)->car=car;
	obj->cdr=0;
	obj->refs=0;
	DEBUG(fprintf(stderr,"New object: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	return (obj_t *)obj;
}
void destroy(obj_t *obj)
{
	DEBUG(fprintf(stderr,"Destroying: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	switch (obj->type) {
		case FUNCTION:
			destroy_func(obj);
			break;
		case SYMBOL:
			free((char *)obj->car);
		case DOUBLE:
		case INTEGER:
			free(obj);
			break;
		case CELL:
			dec_rc((obj_t *)obj->car);
			dec_rc((obj_t *)obj->cdr);
			free(obj);
		default:
			break;
	}
}
void destroy_func(obj_t *obj)
{
	long size=obj->cdr;
	obj_t **f=(obj_t **)obj->car;
	for (int i=0;i<size;i++)
		dec_rc(f[i]);
	free(f);
	free(obj);
}
void inc_rc(obj_t *obj)
{
	if (!obj)
		return;
	DEBUG(fprintf(stderr,"refs++: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	obj->refs+=obj->refs>=0;
}
void dec_rc(obj_t *obj)
{
	if (!obj)
		return;
	DEBUG(fprintf(stderr,"refs--: "); print_obj(obj,stderr,true); fputc('\n',stderr);)
	obj->refs-=obj->refs>0;
	if (!obj->refs)
		destroy(obj);
}
