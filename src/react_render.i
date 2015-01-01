%module react_render
%{
        #include "react_render.h"
%}

%rename(initialize) render_init;

extern int render_init(char *path);
extern char *render_element(char *element);
