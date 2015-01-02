DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/react_render.c src/react_render.h src/react_render.i
SWIG_PYTHON=src/react_render_wrap.c
PYTHON_INCLUDES=-I/usr/include/python2.7
JAVA_INCLUDES=-I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux

main: src/main.c src/react_render.c src/react_render.h
	gcc -std=c99 src/react_render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

swig-python: $(SOURCES)
	rm -rf src/react_render_wrap.c
	swig -python -outdir python/ src/react_render.i

swig-java: $(SOURCES)
	rm -rf src/react_render_wrap.c
	swig -java -outdir java/ src/react_render.i

$(SWIG_PYTHON): swig-python

bundle: app.js
	./node_modules/.bin/webpack

python:  swig-python
	gcc -c -fpic src/react_render.c src/react_render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include $(PYTHON_INCLUDES) -Iduktape-1.0.2/src
	gcc -shared duktape.o react_render.o react_render_wrap.o -o python/_react_render.so

java:  swig-java
	gcc -c -fpic src/react_render.c src/react_render_wrap.c duktape-1.0.2/src/duktape.c -I /usr/local/include $(JAVA_INCLUDES) -Iduktape-1.0.2/src
	gcc -shared duktape.o react_render.o react_render_wrap.o -o java/libreact_render.so

test-python: bundle python
	cd python; python test.py

test-java: bundle java
	cd java; javac Test.java
	cd java; LD_LIBRARY_PATH=. java -classpath . Test

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
