DUKTAPE_HOME=duktape-1.0.2/src
SOURCES=src/react_render.c src/react_render.h src/react_render.i

INCLUDES=-I/usr/local/include -Iduktape-1.0.2/src
PYTHON_INCLUDES=-I/usr/include/python2.7
JAVA_INCLUDES=-I/usr/lib/jvm/java-8-oracle/include -I/usr/lib/jvm/java-8-oracle/include/linux
SWIG_COMPILE=gcc -c -fpic src/react_render.c src/react_render_wrap.c duktape-1.0.2/src/duktape.c

PYTHON_SO=python/_react_render.so
JAVA_SO=java/libreact_render.so
CLOJURE_SO=clojure/libreact_render.so

main: src/main.c src/react_render.c src/react_render.h
	gcc -std=c99 src/react_render.c src/main.c $(DUKTAPE_HOME)/duktape.c -I $(DUKTAPE_HOME) -lm -o main

swig-python: $(SOURCES)
	rm -rf src/react_render_wrap.c
	swig -python -outdir python/ src/react_render.i

swig-java: $(SOURCES)
	rm -rf src/react_render_wrap.c
	mkdir -p java/com/tildedave
	swig -java -outdir java/ src/react_render.i

bundle: app.js
	./node_modules/.bin/webpack

python:  swig-python
	$(SWIG_COMPILE) $(INCLUDES) $(PYTHON_INCLUDES)
	gcc -shared duktape.o react_render.o react_render_wrap.o -o $(PYTHON_SO)

java:  swig-java
	$(SWIG_COMPILE) $(INCLUDES) $(JAVA_INCLUDES)
	gcc -shared duktape.o react_render.o react_render_wrap.o -o $(JAVA_SO)

clojure: java
	cp $(JAVA_SO) $(CLOJURE_SO)

test-python: bundle python
	cd python; python test.py

test-java: bundle java
	cd java; javac Test.java
	cd java; LD_LIBRARY_PATH=. java -classpath . Test

test-clojure: bundle clojure
	cd clojure; cp ../java/react_render*.java .; javac react_render.java
	cd clojure; LD_LIBRARY_PATH=. java -cp clojure-1.6.0/clojure-1.6.0.jar:. clojure.main test.clj

test-clojure-server: bundle clojure
	cp bundle.js clojure/isomorphic-react/resources/public/bundle.js
	cp $(CLOJURE_SO) clojure/isomorphic-react/; \
	cd clojure/isomorphic-react/; \
	lein javac; \
	LD_LIBRARY_PATH=. lein ring server-headless

test-python-server: test-python
	cd python; \
	virtualenv env ; \
	. env/bin/activate; \
	pip install -r requirements.txt ; \
	python flask-server.py

test-c: bundle main
	./main

clean:
	rm -f *.o *.so *.pyc python/*.so
