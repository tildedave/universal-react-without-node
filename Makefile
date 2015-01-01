DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/react_render.c src/react_render.h src/react_render.i
SWIG_PYTHON=src/react_render_wrap.c

main: src/main.c src/react_render.c src/react_render.h
	gcc -std=c99 src/react_render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

$(SWIG_PYTHON): python

python: $(SOURCES)
	swig -python -outdir . src/react_render.i

react_render: $(SOURCES)
	gcc -c -fpic src/react_render.c src/react_render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include -I /usr/include/python2.7 -Iduktape-1.0.2/src
	gcc -shared duktape.o react_render.o react_render_wrap.o -o _react_render.so

bundle: test.js
	./node_modules/.bin/webpack test.js bundle.js

test-python: bundle python react_render
	python test-python.py

test-c: bundle main
	./main

clean:
	rm $(SWIG_PYTHON) *.o *.so *.pyc
