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

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        helpscrn();
    } else if ((strcmp(argv[1], "-i") == 0 || strcmp(argv[1], "--input") == 0) && (argv[2] == NULL)) {
        printf("No input file specified, aborted. \n Exit code: 2\n");
        return 2;
    } else if (argv[2] != NULL) {
        goto input_specified;
    }

input_specified:
    char *file = strdup(argv[2]);

    if (argv[3] == NULL) {
        goto no_output_specified;
    }

    char *flag2 = argv[3];

    if ((strcmp(argv[3], "-o") == 0 || strcmp(argv[3], "--output") == 0) && (argv[4] == NULL)) {
        printf("No output file specified, aborted. \n Exit code: 3\n");
        return 3;
    }

    char *arg2 = argv[4];

    char *flag3 = argv[5];

    if ((strcmp(argv[5], "-t") == 0 || strcmp(argv[5], "--type") == 0) && (argv[6] == NULL)) {
        printf("No output file type specified, aborted. \n Exit code: 4\n");
        return 4;
    }

    char *arg3 = argv[6];

    char *file_extension = ".cyk"; 

    char *file_name_base = strremove(file, file_extension);

    printf(strcat(file_name_base, " \n"));

no_output_specified:
    return 0;
}