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

struct Tokens {
    int tokens[44];
};

int parse(char *input_file_name) {
    FILE *input = fopen(input_file_name, "r");

    struct Tokens bleh = {
        //         "if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", "output", "input", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"
        .tokens = {201, 202, 203, 301, 204, 101, 102, 111, 112, 205, 206, 207, 103, -1, 3, 208, 209, 2, 113, 114, 115, 116, 103, 104, 011, 117, 118, 012, 013, 014, 1, 210, 211, 119, 120, 121, 212, 213, 214, 215, 216, 4, 5, 6}
    };

    char buffer[1024];

    FILE *output = fopen("a.obj", "w+");

    FILE *tmp = fopen("a.txt", "w+");

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if (buffer[0] != 't') {
            fprintf(tmp, "%s", buffer);
        } 
    }
    rewind(tmp);

    fprintf(tmp, "\n\n");

    rewind(input);

    rewind(tmp);

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if (buffer[0] == 't') {
            fprintf(tmp, "%s", &buffer[1]);
        } 
    }

    return 0;
}