#ifndef STACK_H
#define STACK_H
#include "types.h"
#include "memman.h"
#define STACK_SIZE 1024
obj_t *stackitem(int);
void push(obj_t *);
obj_t *pop();
void swap();
void pick(int);
void dupe();
void over();
void nip();
void ndrop(int);
#endif
