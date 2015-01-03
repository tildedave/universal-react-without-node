ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -I$(DUKTAPE)
SUBDIRS = src python java clojure

bundle: app.js
	./node_modules/.bin/webpack
