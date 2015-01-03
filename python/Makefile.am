pkgpython_PYTHON = react_render.py
pkgpyexec_LTLIBRARIES = _react_render.la
_react_render_la_SOURCES = react_render_wrap.c
_react_render_la_CPPFLAGS = $(SWIG_PYTHON_CPPFLAGS) -I$(top_srcdir)/src
_react_render_la_LDFLAGS = -module -shared
_react_render_la_LIBADD = ../src/libreact_render.la

react_render_wrap.c : $(top_srcdir)/react_render.i
	$(SWIG) $(SWIG_PYTHON_OPT) -I$(top_srcdir)/src -o $@ $<
