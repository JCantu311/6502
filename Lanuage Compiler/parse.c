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

struct Tokens {
    int tokens[44];
};

struct Tokens bleh = {
    //         "if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", "output", "input", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"
    .tokens = {201,   202,     203,  301,     204,    101,   102,   111,    112,   205,    206,      207,     103,    -1,     3,         208,     209,         2,       113,   114,    115,    116,   103,     104,    011,   117,   118,     012,   013,     014,    1,       210,  211,  119,    120,        121,      212,  213, 214, 215,  216,   4,      5,      6}
};

char buffer[1024];

typedef void (*FuncPtr)(void);

typedef struct {
    const char *name;
    FuncPtr func;
} FunctionMapping;

void _201() {
    printf("if token");
}

void _202() {
    printf("while token");
}

void _203() {
    printf("do token");
}

void _301() {
    printf("print token");
}

void _204() {
    printf("else token");
}

void _101() {
    printf("add token");
}

void _102() {
    printf("subtract token");
}

FunctionMapping lookup_table[] = {
    {"201", _201},
    {"202", _202},
    {"203", _203},
    {"301", _301},
    {"204", _204},
    {"101", _101},
    {"102", _102},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
    {},
};

int parse_token(FILE *input, FILE *tmp, char *buffer) {
    long buffer2;
    char *endptr;
    char *function_point[4]; 
    function_point[0] = "_";

    if (isdigit(buffer[0])) {
        buffer2 = strtol(buffer, &endptr, 10);
    }
    for(int i = 0; i < 44; i++) {
        if (buffer2 == bleh.tokens[i]) {
            strcat(function_point[0], buffer);
            // token_function = function_point;
            printf("Token: %d\n", bleh.tokens[i]);
        }
    }
}

int parse_parameter(FILE *input, FILE *tmp) {
    printf("PARAMETER PARSED\n");
}

int parse(char *input_file_name) {
    FILE *input = fopen(input_file_name, "r");

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

    rewind(tmp);

    int token_segment = 0;
    int parameter_segment = 0;

    // printf("%d\n", token_segment);
    // printf("%d\n", parameter_segment);

    while(fgets(buffer, sizeof(buffer), tmp) != NULL) {
        // printf("%d\n", token_segment);
        // printf("%d\n", parameter_segment);

        if (strcmp(buffer, "1000\n") == 0) {
            token_segment = 1;
        } else if (strcmp(buffer, "1001\n") == 0) {
            token_segment = 0;
            parameter_segment = 1;
        } else if (token_segment == 1) {
            parse_token(input, tmp, buffer);
        } else if (parameter_segment == 1) {
            parse_parameter(input, tmp);
        }

        // printf("%d\n", token_segment);
        // printf("%d\n", parameter_segment);
    }

    fclose(input);
    fclose(output);
    fclose(tmp);

    return 0;
}