#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "emit.h"
#include "input.h"
#include "etc.h"
#include <ctype.h>

#ifdef _WIN32
    // something idk
#else
    #include <unistd.h>
#endif

void (*token_function)();

void if_function() {
    // something
}

void for_function() {
    // something
}

void while_function() {
    // something
}

void variable_assignment() {
    // something
}

int parse(char *input_file_name) {
    FILE *input = fopen(input_file_name, "r");
    char buffer[1024];

    FILE *output = fopen("a.obj", "w+");

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        printf("%s", buffer);
    }

    return 0;
}