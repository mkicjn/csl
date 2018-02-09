#include "consts.h"
obj_t NIL_OBJ=CONSTANT(NIL);
obj_t *NIL=&NIL_OBJ;
obj_t T_OBJ=CONSTANT(T);
obj_t *T=&T_OBJ;
obj_t SELF_OBJ=CONSTANT(@);
obj_t *SELF=&SELF_OBJ;
obj_t QUOTE_OBJ=CONSTANT(QUOTE);
obj_t *QUOTE=&QUOTE_OBJ;
obj_t PROGN_OBJ=CONSTANT(PROGN);
obj_t *PROGN=&PROGN_OBJ;
obj_t COND_OBJ=CONSTANT(COND);
obj_t *COND=&COND_OBJ;
obj_t ERROR_OBJ=CONSTANT(ERROR);
obj_t ARGS=CONSTANT(<ARGS>); // Exists so special forms know where their arguments end
obj_t CALL=CONSTANT(<CALL>); // Exists to tell `funcall` when to call vs. push a function
obj_t DROP=CONSTANT(<DROP>); // Used in `progn` to discard form evaluations
obj_t COND_DO=CONSTANT(<COND_DO>);
obj_t COND_END=CONSTANT(<COND_END>);
obj_t *ENV=&NIL_OBJ; // Not actually a constant
// Type objects
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
