#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "emit.h"
#include "input.h"
#include "etc.h"

int main(int argc, char *argv[]) {
    if (argc > 7) {
        printf("Too many arguments, aborted. \n Exit code: 1\n");
        return 1;
    } else if (argc < 2) {
        printf("Usage: [options]\n");
        printf("Options:\n");
        printf("    --help      -h              Show help\n");
        printf("    --input     -i              Name input file (to compile)\n");
        printf("    --output    -o              Name output file (always .s or .bin)\n");
        printf("    --type      -t              Output File Type (Assembly or Binary)\n");
        return 1;
    }

    char *flag = argv[1];

    char *file = argv[2];

    char *flag2 = argv[3];

    char *arg2 = argv[4];

    char *flag3 = argv[5];

    char *arg3 = argv[6];

    char *file_extension = '.cyk'; 

no_output_specified:

}