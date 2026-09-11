#include "etc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

void helpscrn() {
    printf("Usage: [options]\n");
    printf("Cykompiler v0.1\n");
    printf("Options:\n");
    printf("    --help      -h              Show help\n");
    printf("    --input     -i              Name input file (to compile)\n");
    printf("                Input file must be .cyk file extension or compilation will fail.\n");
    printf("    --output    -o              Name output file (always .s or .bin)\n");
    printf("                Output name must not have any file extension; the compiler will \nadd it for you");
    printf("    --type      -t              Output File Type (Assembly or Binary)\n");
    printf("                Output file type must be either 'asm' or 'bin'; if not specified,\n the default output type is 'asm'.\n");
}
