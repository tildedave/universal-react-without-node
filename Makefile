DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/render.c src/render.h src/render.i

main: src/main.c src/render.c src/render.h
	gcc -std=c99 src/render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

python: src/render.i $(SOURCES)
	swig -python src/render.i

render: $(SOURCES)
	gcc -c -fpic src/render.c render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include -I /usr/include/python2.7 -Iduktape-1.0.2/src
	gcc -shared duktape.o render.o render_wrap.o -o _render.so

bundle: test.js
	./node_modules/.bin/webpack test.js bundle.js

test-python: bundle python render
	python -c 'import render'

test-c: bundle main
	./main
