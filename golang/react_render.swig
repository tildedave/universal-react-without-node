%module react_render
%{
        #include "react_render.h"
%}

%rename(initialize) render_init;
%rename(set_debug) render_set_debug;

extern int render_init(char *path);
extern char *render_element(char *element);
extern void render_set_debug(int debug_value);
