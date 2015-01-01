DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/react_render.c src/react_render.h src/react_render.i
SWIG_PYTHON=src/react_render_wrap.c

main: src/main.c src/react_render.c src/react_render.h
	gcc -std=c99 src/react_render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

swig-python: $(SOURCES)
	swig -python -outdir python/ src/react_render.i

swig-golang: $(SOURCES)
	swig -go -intgosize 32 -outdir golang/ -package main src/react_render.i

$(SWIG_PYTHON): python

react_render: $(SOURCES)
	gcc -c -fpic src/react_render.c src/react_render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include -I /usr/include/python2.7 -Iduktape-1.0.2/src
	gcc -shared duktape.o react_render.o react_render_wrap.o -o _react_render.so

bundle: app.js
	./node_modules/.bin/webpack

python: react_render swig-python
	cp _react_render.so python/

golang: react_render swig-golang
	cp _react_render.so golang/
	rm -f golang/react_render.a
	cd golang; \
	go tool 6g react_render.go; \
	go tool 6c -I /usr/local/go/pkg/linux_amd64 react_render_gc.c ; \
	go tool pack c react_render.a react_render.6 react_render_gc.6 _react_render.so

test-python: bundle python
	cd python; python test.py

test-golang: bundle golang
	cd golang; go tool 6g test.go react_render.go; go tool 6l test.6

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
