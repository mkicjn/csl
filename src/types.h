#ifndef TYPES_H
#define TYPES_H
typedef enum {false,true} bool;
typedef enum {CELL,SYMBOL,INTEGER,FUNCTION,DOUBLE,ERROR} type_t;
typedef struct {
	type_t type;
	long car,cdr;
	int refs;
} obj_t;
typedef struct {
	type_t type;
	double car,cdr;
	int refs;
} dobj_t; // To avoid typecasting double->long
#define core(name,argc) obj_t * // Info for dictionary code generator
#endif
