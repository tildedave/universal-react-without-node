#include "duktape.h"
#include "config.h"
#include <stdarg.h>

duk_context *ctx;

int _debug = 0;

void render_set_debug(int debug_value) {
        _debug = debug_value;
}

void debug(const char *fmt, ...) {
        va_list args;

        if (_debug) {
                va_start(args, fmt);
                vprintf(fmt, args);
                va_end(args);
        }
}

void error(const char *fmt, ...) {
        va_list args;

        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
}

int render_init(const char *bundle_file) {
    ctx = duk_create_heap_default();
    if (duk_pcompile_file(ctx, 0, bundle_file) != 0) {
            debug("Compile error: %s\n", duk_safe_to_string(ctx, -1));
    } else if (duk_pcall(ctx, 0)) {
            debug("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
    } else {
            debug("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));
    }
}

char *render_path(const char *path) {
        int len;
        char *buf;

        duk_eval_string(ctx, "renderPath");
        duk_push_sprintf(ctx, "%s", path);
        if (duk_pcall(ctx, 1)) {
                error("Error rendering as string: %s\n", duk_safe_to_string(ctx, -1));
                return 0;
        }
        debug("Successfully rendered string: %s\n", duk_safe_to_string(ctx, -1));

        /* TODO: figure out UTF8 */
        len = duk_get_length(ctx, -1);
        buf = malloc(len + 1);
        strncpy(buf, duk_safe_to_string(ctx, -1), len + 1);
        buf[len] = '\0';

        duk_pop(ctx);

        return buf;
}

char *render_element(const char *element, const char *props_as_json) {
        return 0;
}
