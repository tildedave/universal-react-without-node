
#include "runtime.h"
#include "cgocall.h"

#pragma dataflag 16
static void *cgocall = runtime·cgocall;
#pragma dataflag 16
void *·_cgo_runtime_cgocall = &cgocall;


#pragma dynimport _wrap_initialize _wrap_initialize ""
#pragma cgo_import_static _wrap_initialize
extern void _wrap_initialize(void*);
uintptr ·_wrap_initialize = (uintptr)_wrap_initialize;




#pragma dynimport _wrap_render_element _wrap_render_element ""
#pragma cgo_import_static _wrap_render_element
extern void _wrap_render_element(void*);
uintptr ·_wrap_render_element = (uintptr)_wrap_render_element;




#pragma dynimport _wrap_set_debug _wrap_set_debug ""
#pragma cgo_import_static _wrap_set_debug
extern void _wrap_set_debug(void*);
uintptr ·_wrap_set_debug = (uintptr)_wrap_set_debug;




