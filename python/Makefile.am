pkgpython_PYTHON = react_render.py
pkgpyexec_LTLIBRARIES = _react_render.la
_react_render_la_SOURCES = react_render_wrap.c
_react_render_la_CPPFLAGS = $(SWIG_PYTHON_CPPFLAGS) -I$(top_srcdir)/src
_react_render_la_LDFLAGS = -module -shared -avoid-version
_react_render_la_LIBADD = ../src/libreact_render.la

react_render_wrap.c : $(top_srcdir)/react_render.i
	$(SWIG) $(SWIG_PYTHON_OPT) -I$(top_srcdir)/src -o $@ $<

check : _react_render.la
	cp .libs/_react_render.so _react_render.so
	python test.py && echo "Checked!"

test-server :
	virtualenv env
	. env/bin/activate ; pip install -r requirements.txt ; python flask-server.py

clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf *.pyc
	-rm -rf react_render_wrap.c
	-rm -rf react_render.py
	-rm -rf _react_render.so
