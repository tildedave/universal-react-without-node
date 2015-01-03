lib_LTLIBRARIES = libreact_render.la
libreact_render_la_SOURCES = react_render_wrap.c
libreact_render_la_CPPFLAGS = $(JAVA_CPPFLAGS) -I$(top_srcdir)/src
libreact_render_la_LDFLAGS = -module -shared -avoid-version
libreact_render_la_LIBADD = ../src/libreact_render.la

react_render_wrap.c : $(top_srcdir)/react_render.i
	$(SWIG) -java $(JAVA_CPPFLAGS) -I$(top_srcdir)/src -o $@ $<

check : libreact_render.la
	cp .libs/libreact_render.so libreact_render.so
	javac Test.java && LD_LIBRARY_PATH=. java -classpath . Test && echo "Checked!"

clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf *.class
	-rm -rf libreact_render.so
	-rm -rf react_render_wrap.c
	-rm -rf react_render.java
	-rm -rf react_renderJNI.java
