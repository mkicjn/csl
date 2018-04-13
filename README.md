## My name is Mark Johnson, and I referenced this work in my Entry-to-a-Major application at Texas A&M University. This note is intended to prove my ownership of the project to any faculty who see it.

# csl
An amateur LISP dialect with a stack-based bytecode compiler/interpreter based on translation to RPN

(i.e. a garbage-collected redo of stacklisp in C instead of x64 assembly, but with way more features)

##### To-do list:
* Manage environments better to make temporary bindings more sensible
* Find and fix more of the rare issues with memory management
* An embedded Forth-like syntax
* More math functions (`sin`, `exp`, `ln`, etc.)
* Better error handling

To see a list of all primitive functions in the language, do `cat src/*.h | sed -n 's/^[^#]*core(\([^,]*\).*/\1/p'`

### Usage notes:

Build with `make`.

With no arguments, the executable enters a REPL. First argument to the executable is loaded and evaluated like a script (its return value not printed).

Scripts can also start with a shebang (i.e. `#!/usr/local/bin/csl`) and be marked as executable to be run like any script written in Perl, Bash, etc.

##### Specific points:
* This "compiler" works by translating LISP code to reverse Polish notation, and "compiling" it into a "threaded" "bytecode" (a series of addresses) for the "bytecode" interpreter.
  * I don't know whether my usage of this terminology is legitimate because I haven't taken CS in college yet.
* `progn` exists, and is *never* implicit, without exception.
* Quotations are never implicit, with a single exception, explained below. Part of the reason for this is so that the argument list and body given to `lambda` can be generated by another function, or be a variable.
* The exception to the above rule is with "macros". When using curly braces instead of parentheses, the reader implicitly quotes the arguments and applies `eval` to the return value of the function application.
  * See `let` in functions.lisp for an example of how such a function would be implemented.
* List splicing akin to Common Lisp's is implemented. `` `(...) `` where `...` may contain expressions which are quoted by default and may be preceded by `'`, `:`, or `\`, which add `quote`, place in list, or splice into list respectively.
* Such syntax features are implemented purely through the reader. The reader deals with special syntax by transforming it into the long-form equivalent. All syntax features are essentially shorthand.
  * e.g. `` `(:x \`(\x 'c)) `` => `(CONS x (APPEND (APPEND x (CONS (QUOTE (QUOTE c)) NIL)) NIL))`
  * e.g. `{f x y}` => `(EVAL (f (QUOTE x) (QUOTE y)))`
  * e.g. `'x`=>`(QUOTE x)`
* Strings (with quotation marks) are symbols and must be quoted as such. Otherwise, the reader interprets it as a variable. In effect, this allows the programmer to make variables that have spaces and other characters in them.
  * `print` works as Common Lisp's `princ`
  * `output` works as Common Lisp's `prin1`
* Symbols are case sensitive
* Line comments go after a pound sign, i.e. `# ...`
* Block comments go between tildes, e.g. `~...~`
* For conditionals, `cond` exists, but not `if` (although you could easily implement it in the language as a macro)
  * I might add `if` in the future
* There are two functions for declaring variables:
  1. `define` - Bindings from `define` are *very* temporary. They are only really intended exist inside `progn` forms.
  2. `declare` - Bindings from `declare` are permanent and global.
* `load` does not evaluate its result. There are two options for this:
  1. Apply `eval` explicitly, e.g. `(eval (load 'functions.lisp))`
  2. Treat `load` as a macro, e.g. `{load functions.lisp}` (it is expected that the file contain code)
* Symbols/forms can be outputted to a file by `(file_out 'filename thing)`
  * They are outputted with what is in effect `output`, so symbols made with quotation marks can be read back in.
* Bad argument types to functions generally return `ERROR`, e.g. `(+ 1 'a)` => `ERROR`
  * There may be some places where a segfault is caused instead of returning `ERROR`. This is an oversight.
* The special forms `cond` and `progn` work with special translation rules.
* The `see` function "disassembles" a given function argument, returning the result of turning its "compiled" "bytecode" into a regular old linked list, like every other object.
* `funcall` does not exist to the language; it is completely redundant as everything inside a form is evaluated already, including the function to be applied.
  * i.e. `(funcall (if (> a b) - +) a b)` would be written as `((cond ((> a b) -) (t +)) a b)`
* Variadic functions are possible. Use the symbol `VARIADIC` (case-insensitive) in place of arguments. This binds arguments to the symbol `ARGV`.
  * e.g. `(declare 'sum (lambda variadic '(reduce + argv)))`
* The arithmetic operators are not variadic, but can easily be redefined to be variadic
  * e.g. ``(declare '+ (lambda variadic `(:(lambda '(l) `(cond (l (:+ (car l) (@ (cdr l)))) (t 0))) argv)))``
  * Note in the above example that splices can be used to insert pre-compiled functions into function bodies so that they do not get recompiled with every call to the function.

##### "Fun" facts:
* This project was originally written in x64 assembly but was not garbage collected. In fact, it was my second real project in assembly, and was the proving ground for teaching myself assembly.
  * My first real assembly project was a hash table implementation, which I had already written in C.
  * The difficulty in adding garbage collection to an already-"finished" assembly project (stacklisp) was actually the reason I decided to redo (not rewrite) the project in C. I wanted a tool, and not a toy, but adding it was a chore.
  * I knew I wanted to use reference counting, but finding everywhere a reference is created or destroyed in a few thousand lines of assembly is not fun. After getting bored with it, I decided it would be more fun to redo everything.
  * The original assembly project used the call stack to hold values. I just wanted to see if I could do it, and I could.
  * The original idea for the project came when I figured that since both prefix notation and reverse Polish notation has no ambiguity (with order of operations), it should be possible to translate one into the other. I like LISP and Forth, so it was not a large leap in logic that I should try to build something like this.
* I wrote a minimal LISP interpreter in C a long time ago (also on Github), but it was very buggy and had deep fundamental design flaws. In my opinion, this project is already *almost* as usable as a real compiler/interpreter, and will be when I finish fixing the odd automatic memory management flaws (the occasional invalid free() or slight memory leak).
* `(eval f)` is functionally identical to `((lambda nil f))`.
* On my laptop, calculating 100 factorial takes 3 milliseconds.

Examples available in functions.lisp
