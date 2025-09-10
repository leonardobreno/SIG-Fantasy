#include <stdio.h>

void limpar_buffer(void) {
    int c;
    c = getchar();
    while ((c != '\n' && c != EOF)) {
        c = getchar();
    };
}