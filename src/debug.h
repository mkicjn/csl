// To use, place expressions to be evaluated in debug mode inside the DEBUG macro.
// To enable such expressions in a block, do `#define DEBUG DEBUG_ON` and `#define DEBUG DEBUG_OFF`.
// The compiler will give a warning about redefining the macro. This can serve as a reminder that it is enabled somewhere.
#ifndef DEBUG_H
#define DEBUG_H
#define DEBUG DEBUG_OFF
#define DEBUG_ON(a) a
#define DEBUG_OFF(a)
#endif
