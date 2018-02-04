CC=clang
CFLAGS=-O3 -g

csl: *.c
	ls | sed -n '/lisp.h/!s/.*\.h/#include \"&\"/p' > lisp.h
	./gen_dict core.h arith.h
	$(CC) -o csl *.c $(CFLAGS)
