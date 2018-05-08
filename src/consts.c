#include "consts.h"
// Constants directly available to language
NEW_CONSTANT(NIL);
NEW_CONSTANT(T);
NEW_CONSTANT(RECURSE);
NEW_CONSTANT(QUOTE);
NEW_CONSTANT(PROGN);
NEW_CONSTANT(COND);
NEW_CONSTANT(VARIADIC);
NEW_CONSTANT(ARGV);
NEW_CONSTANT(GO);
dobj_t PI_OBJ={
	.type=DOUBLE,
	.car=M_PI,
	.refs=-1
};
obj_t *PI=(obj_t *)&PI_OBJ;
// Constants normally unavailable to language
// (These require the address operator as distinction)
obj_t ARGS=CONSTANT(<ARGS>); // Exists so special forms know where their arguments end
obj_t ERROR_OBJ=CONSTANT(ERROR);
obj_t CALL=CONSTANT(<CALL>); // Exists to tell `funcall` when to call vs. push a function
obj_t DROP=CONSTANT(<DROP>); // Used in `progn` to discard form evaluations
obj_t COND_BEGIN=CONSTANT(<COND_BEGIN>);
obj_t COND_DO=CONSTANT(<COND_DO>);
obj_t COND_DONE=CONSTANT(<COND_DONE>);
obj_t COND_END=CONSTANT(<COND_END>);
// Type symbols (i.e. type's return values)
obj_t INTEGER_OBJ=CONSTANT(INTEGER);
obj_t DOUBLE_OBJ=CONSTANT(DOUBLE);
obj_t FUNCTION_OBJ=CONSTANT(FUNCTION);
obj_t CELL_OBJ=CONSTANT(CELL);
obj_t SYMBOL_OBJ=CONSTANT(SYMBOL);
obj_t *type_objs[5]={
	&CELL_OBJ,
	&SYMBOL_OBJ,
	&INTEGER_OBJ,
	&FUNCTION_OBJ,
	&DOUBLE_OBJ
};
// Not actually constant
obj_t *ENV=&NIL_OBJ;
