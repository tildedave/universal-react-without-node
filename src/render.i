%module render
%{
        extern int render_init();
        extern int render_element(char **buf, char *element);
%}
