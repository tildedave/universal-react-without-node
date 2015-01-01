%module render
%{
        #include "render.h"
%}

extern int render_init();
extern char *render_element(char *element);
