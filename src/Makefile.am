AM_CFLAGS = -shared -std=c99 -I$(DUKTAPE) -lm

lib_LTLIBRARIES = libreact_render.la
libreact_render_la_SOURCES = react_render.c $(DUKTAPE)/duktape.c

check_PROGRAMS = react_render_check
react_render_check_SOURCES = react_render_check.c
react_render_check_LDADD = libreact_render.la -lcheck

check : react_render_check
	./react_render_check && echo "Checked!"
