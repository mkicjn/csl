# csl
A garbage-collected rewrite of stacklisp in C

##### To-do list:
* Manage environments better to make temporary bindings easier
* Find and fix more of the rare issues with memory management
* More math functions
* Better error handling

To see a list of all primitive functions in the language, do `cat src/*.h | sed -n 's/^[^#]*core(\([^,]*\).*/\1/p'`
