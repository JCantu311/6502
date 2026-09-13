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
        no_args_scrn();
    }

    char *inputs_buffered[7] = {NULL};

    char *inputs[8] = {NULL};

    for(int i = 0; i < argc; i++) {
        inputs_buffered[i] = argv[i];
    }

    for(int i = 0; i < 6; i++) {
        inputs[i] = inputs_buffered[i + 1];
    }

no_output:
    char *file_extension = ".cyk"; 
    char *file_name;

    if(output_flag == 1 && inputs[3] != NULL) {

    }

    if (inputs[1] == NULL) {
        printf("No input file specified, aborting. \n Exit code: 2\n");
        return 2;
    } else if (inputs[1] != NULL) {
        inputs[6] = strremove(inputs[1], file_extension);
    }
    printf("Bleh 4\n");

    if ((output_flag != NULL) && (inputs[3] == NULL)) {
        printf("No output file specified, assuming default output name: \n %s\n", inputs[6]);
    }
    printf("%s\n", inputs[3] ? inputs[3] : "NULL");

    if ((inputs[5] == NULL) && (type_flag != NULL)) {
        printf("No output type specified, assuming default output type: \n .s.\n");
    }
    printf("Bleh 6\n");

    printf("%s\n\n", inputs[6]);

    for(int i = 0; i < 8; i++) {
        printf("%s\n", inputs[i] ? inputs[i] : "NULL");
    }

    return 0;
}