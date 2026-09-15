#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "emit.h"
#include "input.h"
#include "etc.h"

#ifdef _WIN32
    #include <io.h>
    #include <process.h>
#else
    #include <unistd.h>
#endif


int lex(char *inputs[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%s\n", inputs[i] ? inputs[i] : "NULL");
    }

    FILE *input_file = fopen(inputs[4], "r");
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        remove_spaces(buffer);
        printf("%s", buffer);
    }
    printf("\n");

    fclose(input_file);

    return 0;
}