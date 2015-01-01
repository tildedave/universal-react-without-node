#include <stdio.h>
#include <stdlib.h>
#include "render.h"

int main(int arc, char *argv[]) {
        char *buf;

        render_init();
        buf = render_element("A");
        printf("Successfully rendered buffer: %s\n", buf);
        free(buf);

        buf = render_element("UnknownElement");
        if (buf) {
                printf("Successfully failed to render buffer\n");
        }

        return 0;
}
