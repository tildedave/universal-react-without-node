#include <stdio.h>
#include "duktape.h"

int render_element(duk_context *ctx, char **buf, char *element) {
        int len;

        duk_eval_string(ctx, "React.renderToString");
        duk_eval_string(ctx, "React.createElement");
        duk_push_sprintf(ctx, "ReactElements.%s", element);
        duk_eval(ctx);

        if (duk_is_undefined(ctx, -1)) {
                printf("Could not find React Element %s\n", element);
                return 1;
        } else if (duk_pcall(ctx, 1)) {
                printf("Error creating Element: %s\n", duk_safe_to_string(ctx, -1));
                return 1;
        } else if (duk_pcall(ctx, 1)) {
                printf("Error rendering as string: %s\n", duk_safe_to_string(ctx, -1));
                return 1;
        }
        printf("So much success rendering as string: %s\n", duk_safe_to_string(ctx, -1));

        /* TODO: UTF8 */
        len = duk_get_length(ctx, -1);
        *buf = malloc(len + 1);
        strncpy(*buf, duk_safe_to_string(ctx, -1), len + 1);
        (*buf)[len] = '\0';

        duk_pop(ctx);
        return 1;
}

int main(int arc, char *argv[]) {
        duk_context *ctx = duk_create_heap_default();

        if (duk_pcompile_file(ctx, 0, "bundle.js") != 0) {
                printf("Compile error: %s\n", duk_safe_to_string(ctx, -1));
        } else if (duk_pcall(ctx, 0)) {
                printf("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
        } else {
                printf("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));

                char *buf;
                render_element(ctx, &buf, "A");
                printf("Rendered buffer: %s\n", buf);
        }

        return 0;
}
