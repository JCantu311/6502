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

    char *inputs_buffered[7] = {NULL};

    char *inputs[8] = {NULL};

    for(int i = 0; i < argc; i++) {
        inputs_buffered[i] = argv[i];
    }

    for(int i = 0; i < 6; i++) {
        inputs[i] = inputs_buffered[i + 1];
    }

    int input_flag = (strcmp(inputs[0], "--input") == 0 || strcmp(inputs[0], "-i") == 0);

    int help_flag = (strcmp(inputs[0], "--help") == 0 || strcmp(inputs[0], "-h") == 0);

    int output_flag = (strcmp(inputs[2], "--output") == 0 || strcmp(inputs[2], "-o") == 0);

    int type_flag = (strcmp(inputs[4], "--type") == 0 || strcmp(inputs[4], "-t") == 0);

    if ((input_flag == 1) && (inputs[1] == NULL)) {
        printf("No input file specified, aborted. \n Exit code: 1\n");
        return 1;
    } else if ((input_flag == 1) && (inputs[1] != NULL)) {
        printf("%s\n\n", inputs[1]);
    } else if ((input_flag != 1) && (help_flag != 1)) {
        printf("Unknown argument, aborted. \n Exit code: 1\n");
        return 1;
    } else if ((input_flag != 1) && (help_flag == 1)) {
        helpscrn();
    } else {
        printf("Aborting.");
        return 1;
    }

    char *file_extension = ".cyk"; 

    inputs[6] = strremove(inputs[1], file_extension);

    printf("%s\n\n", inputs[6]);

    for(int i = 0; i < 8; i++) {
        printf("%s\n", inputs[i] ? inputs[i] : "NULL");
    }

    return 0;
}