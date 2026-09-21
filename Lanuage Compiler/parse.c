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

char *token_function_name[4];

void (*token_function)();

void _201() {
    // something
}

void _() {
    // something
}

void while_function() {
    // something
}

void variable_assignment() {
    // something
}

int parse_token() {
    // something
}

int parse_parameter() {
    // something
}

struct Tokens {
    int tokens[44];
};

int parse(char *input_file_name) {
    FILE *input = fopen(input_file_name, "r");

    struct Tokens bleh = {
        //         "if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", "output", "input", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"
        .tokens = {201,   202,     203,  301,     204,    101,   102,   111,    112,   205,    206,      207,     103,    -1,     3,         208,     209,         2,       113,   114,    115,    116,   103,     104,    011,   117,   118,     012,   013,     014,    1,       210,  211,  119,    120,        121,      212,  213, 214, 215,  216,   4,      5,      6}
    };

    char buffer[1024];

    FILE *output = fopen("a.obj", "w+");

    FILE *tmp = fopen("a.txt", "w+");

    fprintf(tmp, "1000\n");

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if ((buffer[0] == 't') && isdigit(buffer[1])) {
            fprintf(tmp, "%s", &buffer[1]);
        } 
    }

    rewind(input);

    fprintf(tmp, "1001\n");

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if (buffer[0] != 't' || (buffer[0] == 't') && !isdigit(buffer[1])) {
            fprintf(tmp, "%s", buffer);
        } 
    }

    int token_segment = 0;
    int parameter_segment = 0;

    while(fgets(buffer, sizeof(buffer), tmp) != NULL) {
        if (buffer == "1000") {
            token_segment = 1;
        } else if (token_segment == 1) {
            parse_token();
        } else if (buffer == "1001") {
            token_segment = 0;
            parameter_segment = 1;
        } else if (parameter_segment = 1) {
            parse_parameter();
        }
    }

    fclose(input);
    fclose(output);
    fclose(tmp);

    return 0;
}