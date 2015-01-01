%module react_render
%{
        extern int render_init();
        extern char *render_element(char *element);
%}

extern int render_init();
extern char *render_element(char *element);
