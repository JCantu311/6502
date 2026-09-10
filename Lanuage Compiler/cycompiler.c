#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "emit.h"

int main(int argc, char *argv[]) {
    if (argc > 4) {
        printf("Too many arguments, aborted. \n Exit code: 1\n");
        return 1;
    }

    char *flag = argv[1];

    char *file = argv[2];

    char *flag2 = argv[3];

    char *file2 = argv[4];

    printf(flag, "\n");
    printf(file, "\n");
    printf(flag2, "\n");
    printf(file2, "\n");
    for(int i = 0; i < argc; i++) {
        if (strcmp(flag, "-i") == 0 || strcmp(flag, "--input") == 0) {
            printf("Yar har mateys here be the input screen\n");
            return 0;
        }
        if (strcmp(flag, "-o") == 0 || strcmp(flag, "--output") == 0) {
            printf("Yar har mateys here be the output screen\n");
            return 0;
        }
        if (strcmp(flag, "-h") == 0 || strcmp(flag, "--help") == 0) {
            printf("Yar har mateys here be the help screen\n");
            return 0;
        }
    }
    
}