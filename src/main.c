#include <stdio.h>
#include "render.h"

int main(int arc, char *argv[]) {
        char *buf;

        render_init();
        if (render_element(&buf, "A")) {
                return 1;
        }
        printf("Successfully rendered buffer: %s\n", buf);

        if (render_element(&buf, "UnknownElement")) {
                printf("Successfully failed to render buffer\n");
        }

        return 0;
}
