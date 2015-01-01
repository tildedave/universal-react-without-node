DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/react_render.c src/react_render.h src/react_render.i
SWIG_PYTHON=src/react_render_wrap.c

main: src/main.c src/react_render.c src/react_render.h
	gcc -std=c99 src/react_render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

python: $(SOURCES)
	swig -python -outdir python/ src/react_render.i

$(SWIG_PYTHON): python

react_render: $(SOURCES)
	gcc -c -fpic src/react_render.c src/react_render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include -I /usr/include/python2.7 -Iduktape-1.0.2/src
	gcc -shared duktape.o react_render.o react_render_wrap.o -o python/_react_render.so

bundle: app.js
	./node_modules/.bin/webpack

test-python: bundle python react_render
	cd python; python test.py

test-python-server: test-python
	cd python; \
	virtualenv env ; \
	. env/bin/activate; \
	pip install -r requirements.txt ; \
	python flask-server.py

test-c: bundle main
	./main

clean:
	rm -f $(SWIG_PYTHON) *.o *.so *.pyc python/*.so
