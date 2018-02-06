CC=clang
CFLAGS=-O3

csl: repl.c src/*.c
	ls src/*.h | sed -n 's/.*\.h/#include \"&\"/p' > lisp.h
	perl gen_dict src/core.h src/arith.h
	$(CC) -o csl repl.c src/*.c $(CFLAGS)
