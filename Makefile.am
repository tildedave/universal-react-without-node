ACLOCAL_AMFLAGS = -I m4
AM_CFLAGS = -I$(DUKTAPE)
SUBDIRS = src python java clojure

bundle: app.router.js app.element.js
	./node_modules/.bin/webpack
