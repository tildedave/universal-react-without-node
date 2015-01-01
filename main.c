#include <stdio.h>
#include "duktape.h"

char *markup;

/* TODO: better name */
int capture(duk_context *ctx) {
        int len = duk_get_length(ctx, -1);

        /* TODO: portability ¯\_(ツ)_/¯ */
        /* TODO: UTF length issues - no surprise */

        markup = malloc(len + 1);
        strncpy(markup, duk_safe_to_string(ctx, -1), len + 1);
        markup[len] = '\0';

        fprintf(stdout, "captured: %s", duk_safe_to_string(ctx, -1));
        fprintf(stdout, "\n");
        fflush(stdout);

        return 0;
}

int render_element(duk_context *ctx, char **buf, char *element) {
        int len;

        /* This seems overly elaborate */
        duk_get_global_string(ctx, "React");
        duk_get_prop_string(ctx, -1, "renderToString");
        duk_remove(ctx, -2);

        duk_get_global_string(ctx, "React");
        duk_get_prop_string(ctx, -1, "createElement");
        duk_remove(ctx, -2);

        duk_get_global_string(ctx, "ReactElements");
        duk_get_prop_string(ctx, -1, element);
        duk_remove(ctx, -2);

        if (duk_pcall(ctx, 1)) {
                printf("Error creating Element: %s\n", duk_safe_to_string(ctx, -1));
        } else if (duk_pcall(ctx, 1)) {
                printf("Error rendering as string: %s\n", duk_safe_to_string(ctx, -1));
        }
        printf("So much success rendering as string: %s\n", duk_safe_to_string(ctx, -1));

        /* TODO: UTF8 */
        len = duk_get_length(ctx, -1);
        *buf = malloc(len + 1);
        strncpy(*buf, duk_safe_to_string(ctx, -1), len + 1);
        (*buf)[len] = '\0';
}

int main(int arc, char *argv[]) {
        duk_context *ctx = duk_create_heap_default();

        duk_push_global_object(ctx);
        duk_push_c_function(ctx, capture, 1);
        duk_put_prop_string(ctx, -2, "capture");
        duk_pop(ctx);

        if (duk_pcompile_file(ctx, 0, "bundle.js") != 0) {
                printf("Compile error: %s\n", duk_safe_to_string(ctx, -1));
        } else if (duk_pcall(ctx, 0)) {
                printf("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
        } else {
                printf("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));

                /* TODO: figure out wide-character UTF8 */
                printf("Buffer is now available: %s\n", markup);
                /*
                duk_eval_string(ctx, "global.React.version");
                duk_dump_context_stderr(ctx);
                */

                char *buf;
                render_element(ctx, &buf, "A");
                printf("Rendered buffer: %s", buf);
        }

        return 0;
}
