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

int render_init(const char *path) {
    ctx = duk_create_heap_default();
    if (duk_pcompile_file(ctx, 0, path) != 0) {
            debug("Compile error: %s\n", duk_safe_to_string(ctx, -1));
    } else if (duk_pcall(ctx, 0)) {
            debug("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
    } else {
            debug("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));
    }
}

char *render_path(char *element) {
        int len;
        char *buf;

        duk_eval_string(ctx, "render");
        duk_push_sprintf(ctx, "%s", element);
        if (duk_pcall(ctx, 1)) {
                debug("Error rendering as string: %s\n", duk_safe_to_string(ctx, -1));
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
