#include <stdio.h>

#include "version.h"

void logo(void) {
    fprintf(stderr, "▌▐ ▛▘▛▜ UFO version %s\n", UFO_VERSION);
    fprintf(stderr, "▙▟ ▛ ▙▟ http://github.com/ufo-language\n");
    fprintf(stderr, "Type :? for help\n\n");
}
