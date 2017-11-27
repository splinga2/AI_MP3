#include "includes.h"

void pause() {
    char c;
    do {
        c = 'x';
        puts("pause...");
    } while ( (c = getchar()) != '\n' );
}
