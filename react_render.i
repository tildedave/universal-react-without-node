%module react_render
%{
        #include "react_render.h"
%}

%rename(initialize) render_init;
%rename(set_debug) render_set_debug;

%pragma(java) jniclasscode=%{
static {
       try { System.loadLibrary("react_render"); }
       catch (RuntimeException e) {
               System.out.println("Failed to load the C++ libraries during SWIG module initialisation");
               e.printStackTrace();
       }
}
%}

extern int render_init(char *path);
extern char *render_path(char *path);
extern char *render_element(char *element, char *props_as_json);
extern void render_set_debug(int debug_value);
