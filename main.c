#include <stdio.h>
#include "duktape.h"

int capture(duk_context *ctx) {
        fprintf(stdout, "captured: %s", duk_safe_to_string(ctx, -1));
        fprintf(stdout, "\n");
        fflush(stdout);

        return 0;
}

int main(int arc, char *argv[]) {
        duk_context *ctx = duk_create_heap_default();
        /*
        duk_push_global_object(ctx);
        duk_push_c_function(ctx, capture, 1);
        duk_put_prop_string(ctx, -2, "capture");
        duk_pop(ctx);
        */

        if (duk_pcompile_file(ctx, 0, "test2.js") != 0) {
                printf("Compile error: %s\n", duk_safe_to_string(ctx, -1));
        } else {
                duk_call(ctx, 0);
                printf("Result of evaluating was: %s\n", duk_safe_to_string(ctx, -1));
        }

        duk_pop(ctx);

        printf("Hello, world!\n");
        return 0;
}
