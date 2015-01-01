DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/render.c src/render.h src/render.i
SWIG_PYTHON=src/render_wrap.c

main: src/main.c src/render.c src/render.h
	gcc -std=c99 src/render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

$(SWIG_PYTHON): python

python: $(SOURCES)
	swig -python -outdir . src/render.i

render: $(SOURCES)
	gcc -c -fpic src/render.c src/render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include -I /usr/include/python2.7 -Iduktape-1.0.2/src
	gcc -shared duktape.o render.o render_wrap.o -o _render.so

bundle: test.js
	./node_modules/.bin/webpack test.js bundle.js

test-python: bundle python render
	python test-python.py

test-c: bundle main
	./main

clean:
	rm $(SWIG_PYTHON) *.o *.so *.pyc
