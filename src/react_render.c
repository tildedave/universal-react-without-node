#include "duktape.h"
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

char *render_result;

int capture_render_result() {
        /* TODO: portability ¯\_(ツ)_/¯ */
        int len = duk_get_length(ctx, -1);
        render_result = malloc(len + 1);
        strncpy(render_result, duk_safe_to_string(ctx, -1), len);
        render_result[len] = '\0';

        fprintf(stdout, "captured: %s", duk_safe_to_string(ctx, -1));
        fprintf(stdout, "\n");
        fflush(stdout);

        return 0;
}

void info(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
}

int render_init(const char *path) {
    ctx = duk_create_heap_default();
    if (duk_pcompile_file(ctx, 0, path) != 0) {
            debug("Compile error: %s\n", duk_safe_to_string(ctx, -1));
    } else if (duk_pcall(ctx, 0)) {
            info("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
    } else {
            debug("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));
    }
}

char *render_element(char *element) {
        int len;
        char *buf;

        duk_eval_string(ctx, "render");
        duk_push_sprintf(ctx, "%s", element);
        duk_push_c_function(ctx, capture_render_result, 1);

        if (duk_pcall(ctx, 2)) {
                info("Error rendering as string: %s\n", duk_safe_to_string(ctx, -1));
                return 0;
        }
        debug("Successfully rendered string: %s\n", duk_safe_to_string(ctx, -1));

        len = strlen(render_result);
        buf = malloc(len);
        strncpy(buf, render_result, len);
        buf[len] = '\0';

        /* Pop result of pcall - it was not used */
        duk_pop(ctx);

        return buf;
}
