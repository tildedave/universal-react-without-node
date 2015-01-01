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

int main(int arc, char *argv[]) {
        duk_context *ctx = duk_create_heap_default();

        duk_push_global_object(ctx);
        duk_push_string(ctx, "{}");
        duk_put_prop_string(ctx, -2, "global");
        duk_pop(ctx);

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

                duk_pop(ctx);

                duk_get_global_string(ctx, "React");
                duk_get_prop_string(ctx, -1, "renderToString");
                duk_push_string(ctx, "abc");

                if (duk_pcall(ctx, 1)) {
                        printf("Evaluation error: %s\n", duk_safe_to_string(ctx, -1));
                } else {
                        printf("Result of evaluating was: %s\n",
                               duk_safe_to_string(ctx, -1));
                }
        }

        return 0;
}
