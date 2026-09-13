#include "etc.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *strremove(char *str, const char *sub) {
    char *buffer = malloc(strlen(str) + 1);
    strcpy(buffer, str);
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = buffer;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return buffer;
}

void helpscrn() {
    printf("Usage: [options]\n");
    printf("Cykompiler v0.1\n");
    printf("Options:\n");
    printf("    --help      -h              Show help\n");
    printf("    --input     -i              Name input file (to compile)\n");
    printf("                Input file must be .cyk file extension or compilation will fail.\n");
    printf("    --output    -o              Name output file (always .s or .bin)\n");
    printf("                Output name must not have any file extension; the compiler will \nadd it for you\n");
    printf("    --type      -t              Output File Type (Assembly or Binary)\n");
    printf("                Output file type must be either 'asm' or 'bin'; if not specified,\n the default output type is 'asm'.\n");
}

void flag_allocations() {
    int input_flag = NULL;

    int help_flag = NULL;

    int output_flag = NULL;

    int type_flag = NULL;

    if (inputs[0] == NULL) {
        goto no_args;
    } else if (strcmp(inputs[0], "--help") == 0 || strcmp(inputs[0], "-h") == 0) {
        helpscrn();
        return 1;
    } else if (inputs[0] != NULL) {
        input_flag = (strcmp(inputs[0], "--input") == 0 || strcmp(inputs[0], "-i") == 0);
        printf("Bleh\n");
    }

    if (inputs[2] == NULL) {
        goto no_output;
    } else if (inputs[2] != NULL) {
        int output_flag = (strcmp(inputs[2], "--output") == 0 || strcmp(inputs[2], "-o") == 0);
        printf("Bleh 3\n");
    }

    if ((inputs[4] == NULL) && (output_flag != NULL)) {
        printf("No output type specified, assigning default value.\n");
        inputs[8] = ".s";
    } else if ((inputs[4] != NULL) && (output_flag != NULL)) {
        int type_flag = (strcmp(inputs[4], "--type") == 0 || strcmp(inputs[4], "-t") == 0);
        printf("Bleh 4\n");
    }

    if ((input_flag == 1) && (inputs[1] == NULL)) {
    no_input:
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
}