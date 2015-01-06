#include "duktape.h"
#include "config.h"
#include <stdarg.h>

duk_context *ctx;

int _debug = 0;

struct react_element {
        char *name;

        struct react_element *next;
};

struct react_element *elements = 0;

void render_set_debug(int debug_value) {
        _debug = debug_value;
}

void debug(const char *fmt, ...) {
        va_list args;

        if (_debug) {
                va_start(args, fmt);
                vfprintf(stderr, fmt, args);
                va_end(args);
        }
}

void error(const char *fmt, ...) {
        va_list args;

        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
}

int register_element(duk_context *ctx) {
        struct react_element *last = elements;

        // this could be a lot cleaner
        while(last->next != NULL) {
                last = last->next;
        }

        last->next = malloc(sizeof(struct react_element));
        last = last->next;

        duk_size_t len;
        duk_get_lstring(ctx, -2, &len);

        last->name = malloc((unsigned long) len + 1);
        last->next = 0;

        strncpy(last->name, duk_get_string(ctx, -2), (unsigned long) len);
        last->name[len] = '\0';

        duk_remove(ctx, -2);
        duk_eval_string(ctx, "__ReactElements");
        duk_swap(ctx, -1, -2);
        duk_put_prop_string(ctx, -2, last->name);
        duk_pop(ctx);

        return 0;
}

int render_init(const char *bundle_file) {
    ctx = duk_create_heap_default();

    duk_push_global_object(ctx);
    duk_push_c_function(ctx, register_element, 2);
    duk_put_prop_string(ctx, -2, "__registerElement");
    duk_push_object(ctx);
    duk_put_prop_string(ctx, -2, "__ReactElements");
    duk_pop(ctx);

    elements = malloc(sizeof(struct react_element));
    elements->name = NULL;
    elements->next = NULL;

    if (duk_pcompile_file(ctx, 0, bundle_file) != 0) {
            debug("Compile error: %s\n", duk_safe_to_string(ctx, -1));
    } else if (duk_pcall(ctx, 0)) {
            debug("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
    } else {
            debug("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));
    }

    // verify that our globals that we need are defined
    if ( duk_peval_string(ctx, "renderElement") ) {
            error("global.renderElement was not defined!  Rendering an element will not be functional.\n");
            return 1;
    }

    if ( duk_peval_string(ctx, "renderPath") ) {
            error("global.renderPath was not defined!  Rendering a path will not be functional.\n");
            return 1;
    }

    return 0;
}

char *copy_buffer(duk_context *ctx, int idx) {
        char *buf;

        duk_size_t len;
        duk_get_lstring(ctx, idx, &len);
        buf = malloc((unsigned long)len + 1);
        strncpy(buf, duk_safe_to_string(ctx, idx), (unsigned long)len);
        buf[(unsigned long)len] = '\0';

        duk_pop(ctx);

        return buf;
}

char *render_element(const char *element, const char *props_as_json) {
        struct react_element *ele = elements->next;

        while (ele != NULL && strcmp(ele->name, element) != 0) {
                ele = ele->next;
        }

        if (ele == NULL) {
                error("Requested rendering an unknown element: %s\n", element);
                return 0;
        }

        duk_eval_string(ctx, "renderElement");
        duk_push_string(ctx, ele->name);

        if (props_as_json != NULL) {
                duk_push_string(ctx, props_as_json);
                duk_json_decode(ctx, -1);
                duk_dump_context_stderr(ctx);
        } else {
                duk_push_null(ctx);
        }

        if (duk_pcall(ctx, 2)) {
                error("Error evaluating: %s\n", duk_safe_to_string(ctx, -1));
                return 0;
        }

        debug("Successfully rendered string: %s\n", duk_safe_to_string(ctx, -1));

        return copy_buffer(ctx, -1);
}

char *render_path(const char *path) {
        duk_eval_string(ctx, "renderPath");
        duk_push_sprintf(ctx, "%s", path);
        if (duk_pcall(ctx, 1)) {
                error("Error rendering as string: %s\n", duk_safe_to_string(ctx, -1));
                return 0;
        }
        debug("Successfully rendered string: %s\n", duk_safe_to_string(ctx, -1));

        return copy_buffer(ctx, -1);
}

void render_reset() {
        duk_destroy_heap(ctx);
        struct react_element *element = elements;
        struct react_element *next = NULL;

        while(element != NULL) {
                if (element->name) {
                        free(element->name);
                }
                if (element->next) {
                        next = element->next;
                        free(element);
                        element = next;
                }
                element = element->next;
        }

        element = NULL;
}
