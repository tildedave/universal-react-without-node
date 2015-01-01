DUKTAPE_HOME=duktape-1.0.2/src

main:
	gcc -std=c99 main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

bundle: test.js
	./node_modules/.bin/webpack test.js bundle.js

test: bundle main
	./main
	duktape-1.0.2/duk bundle.js
