#ifndef READER_H
#define READER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "core.h"
#include "dict.h"
#include "memman.h"
#include "stack.h"
#include "types.h"
char *ltrim(char *);
bool valid_list(char *);
type_t infer_type(char *);
char *get_word(char *);
char *get_list(char *);
char *get_token(char *);
obj_t *quote(obj_t *);
obj_t *to_list(char *);
obj_t *to_obj(char *);
obj_t *to_splice(char *);
#endif
