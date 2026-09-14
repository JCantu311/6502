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
    no_args:
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

    int input_flag = NULL;

    int help_flag = NULL;

    int output_flag = NULL;

    int type_flag = NULL;

    for(int i = 0; i < argc; i++) {
        inputs_buffered[i] = argv[i];
    }

    for(int i = 0; i < 6; i++) {
        inputs[i] = inputs_buffered[i + 1];
    }

    for(int i = 0; i < 6; i++) {
        printf("%s\n", inputs[i]);
    }

    printf("Bleh 0");

    if (inputs[0] == NULL) {
        goto no_args;
    } else if (strcmp(inputs[0], "--help") == 0 || strcmp(inputs[0], "-h") == 0) {
        helpscrn();
        return 1;
    } else if (inputs[0] != NULL) {
        input_flag = (strcmp(inputs[0], "--input") == 0 || strcmp(inputs[0], "-i") == 0);
    }
    printf("Bleh 1\n");

    if (inputs[2] == NULL) {
        goto no_output;
    } else if (inputs[2] != NULL) {
        int output_flag = (strcmp(inputs[2], "--output") == 0 || strcmp(inputs[2], "-o") == 0);
    }
    printf("Bleh 2\n");

    if ((inputs[4] == NULL) && (output_flag != NULL)) {
        printf("No output type specified, assigning default value.\n");
        inputs[8] = ".s";
    } else if ((inputs[4] != NULL) && (output_flag != NULL)) {
        int type_flag = (strcmp(inputs[4], "--type") == 0 || strcmp(inputs[4], "-t") == 0);
    }
    printf("Bleh 3\n");

    if ((input_flag == 1) && (inputs[1] == NULL)) {
    no_input:
        printf("No input file specified, aborting. \n Exit code: 1\n");
        return 1;
    } else if ((input_flag == 1) && (inputs[1] != NULL)) {
        
    } else if ((input_flag != 1) && (help_flag != 1)) {
        unknown_argument_error();
    } else if ((input_flag != 1) && (help_flag == 1)) {
        helpscrn();
    } else {
        printf("Aborting.");
        return 1;
    }
    printf("Bleh 4\n");

no_output:
    char *file_extension = ".cyk"; 
    char *file_name;
    char *file_type;

    if (input_flag != 1 || help_flag != 1) {
        unknown_argument_error();
    }
    printf("Bleh 5\n");

    if (output_flag != NULL && output_flag != 1){
        unknown_argument_error();
    }
    printf("Bleh 6\n");

    if (type_flag != NULL && type_flag != 1) {
        unknown_argument_error();
    }
    printf("Bleh 7\n");
    
    if (inputs[1] == NULL) {
        printf("No input file specified, aborting. \n Exit code: 2\n");
        return 2;
    } else if (inputs[1] != NULL && inputs[3] == NULL) {
        inputs[6] = strremove(inputs[1], file_extension);
    } else if (inputs[3] != NULL) {
        inputs[6] = inputs[3];
    }

    if(output_flag == 1 && inputs[3] != NULL) {
        file_name = inputs[3];
        file_name = inputs[6];
    } else if (inputs[3] == NULL) {
        printf("No output specified, assigning default:\n %s", inputs[6]);
    }

    if(type_flag == 1 && inputs[5] != NULL) {
        file_type = inputs[5];
    } else if ((inputs[5] == NULL) && (type_flag != NULL)) {
        printf("No output type specified, assuming default output type: \n .s.\n");
        file_type = ".s";
    }
    if (strcmp(inputs[5], "asm")) {
        inputs[7] = ".s";
    } else if(strcmp(inputs[5], "bin")) {
        inputs[7] = ".bin";
    } else if(inputs[5] == NULL) {
        printf("No input specified, assigning default value: \n .s\n");
        inputs[7] = ".s";
    }

    char *inputs_fin[5] = {NULL};

    if(inputs[1] != NULL) {
        inputs_fin[0] = inputs[1];
    }

    if(inputs[6] != NULL) {
        inputs_fin[1] = inputs[6];
    }

    if(inputs[5] != NULL) {
        inputs_fin[2] = inputs[5];
    }

    if(inputs[7] != NULL) {
        inputs_fin[3] = inputs[7];
    }

    for(int i = 0; i < 5; i++) {
        printf("%s\n", inputs_fin[i] ? inputs_fin[i] : "NULL");
    }

    lex(inputs_fin, 5);

    return 0;
}