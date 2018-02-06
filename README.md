# csl
A garbage-collected rewrite of stacklisp in C

##### To-do list:
* Manage environments better to make temporary bindings easier
* Find and fix more of the rare issues with memory management
* More math functions
* Formatted output
* Better error handling

To see a list of all primitive functions in the language, do `cat *.{c,h} | sed -n 's/^[^#]*core(\([^,]*\).*/\1/p'`

To see function prototypes for all C functions, do `cat *.{c,h} | grep -P '^[^#\t]* [^()=]+\(.*\)' | sed 's/ \/\/.*$//;s/\([^;]\)$/\1;/;s/\([(,]\)\([^ *)]*\) \(\**\)\w*/\1\2\3/g;s/\(\w\)\*/\1 \*/g'`
