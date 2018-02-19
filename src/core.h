#ifndef CORE_H
#define CORE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "memman.h"
#include "reader.h"
#include "rpn.h"
#include "stack.h"
#include "types.h"
core(CAR,1) car(obj_t *);
core(CDR,1) cdr(obj_t *);
core(CONS,2) cons(obj_t *,obj_t *);
core(PRINT,1) print(obj_t *);
void print_obj(obj_t *,FILE *fh);
void print_cell(obj_t *,FILE *fh);
core(TERPRI,0) terpri();
core(EQ,2) eq(obj_t *,obj_t *);
core(SET,2) set(obj_t *,obj_t *);
core(RPLACA,2) rplaca(obj_t *,obj_t *);
core(RPLACD,2) rplacd(obj_t *,obj_t *);
obj_t *lread(long);
core(READ,1) oread(obj_t *);
core(ATOM,1) atom(obj_t *);
core(NULL,1) null(obj_t *);
core(NCONC,2) nconc(obj_t *,obj_t *);
core(COPY,1) copy(obj_t *);
core(APPEND,2) append(obj_t *,obj_t *);
core(ASSOC,2) assoc(obj_t *,obj_t *);
core(DECLARE,2) declare(obj_t *,obj_t *);
core(DEFINE,2) define(obj_t *,obj_t *);
core(SYMVAL,1) symval(obj_t *);
core(EXIT,0) l_exit();
core(LIST,0) list();
long length(obj_t *);
core(LENGTH,1) l_length(obj_t *);
core(LAMBDA,2) lambda(obj_t *,obj_t *);
core(SEE,1) see(obj_t *);
void bind_args(obj_t *);
core(FUNCALL,1) funcall(obj_t *);
void do_body(obj_t **,long);
char *slurp(char *);
core(LOAD,1) load(obj_t *);
core(EVAL,1) eval(obj_t *);
core(TYPE,1) type(obj_t *);
core(TYPEP,2) typep(obj_t *,obj_t *);
core(OR,2) or(obj_t *,obj_t *);
core(AND,2) and(obj_t *,obj_t *);
core(FILE_OUT,2) file_out(obj_t *file,obj_t *obj);
#endif
