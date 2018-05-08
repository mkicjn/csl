CC=clang
CFLAGS=-lm -g

csl: repl.c src/*
	ls src/*.h | sed -n 's/.*\.h/#include "&"/p' > lisp.h
	perl gen_dict src/core.h src/arith.h
	$(CC) -o csl repl.c src/*.c $(CFLAGS)

clean:
	rm csl lisp.h src/dict.*
