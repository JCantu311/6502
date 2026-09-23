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
    //         "if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", ".vars", ".endvars", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"
    .tokens = {201,   202,     203,  301,     204,    101,   102,   111,    112,   205,    206,      207,     103,    0,     3,         208,     209,         2,       113,   114,    115,    116,   105,     104,    100,   117,   118,     012,   013,     014,    1,       210,  211,  119,    120,        121,      212,  213, 214, 215,  216,   4,      5,      6}
};

char buffer[1024];

typedef void (*FuncPtr)(void);

FILE *output = NULL;

typedef struct {
    const char *name;
    FuncPtr func;
} FunctionMapping;

void _201() {
    printf("if token\n");
}

void _202() {
    printf("while token\n");
}

void _203() {
    printf("do token\n");
}

void _301() {
    printf("print token\n");
}

void _204() {
    printf("else token\n");
}

void _101() {
    printf("add token\n");
}

void _102() {
    printf("subtract token\n");
}

void _111() {
    printf("multiply token\n");
}

void _112() {
    printf("divide token\n");
}

void _205() {
    printf("read token\n");
}

void _206() {
    fprintf(output, ".segment ZEROPAGE\n");
}

void _207() {
    printf("end variable space token\n");
}

void _103() {
    printf("address var type token\n");
}

void EOF_func() {
    printf("end of file token\n");
}

void _3() {
    printf("include token\n");
}

void _208() {
    printf("endif token\n");
}

void _209() {
    printf("endwhile token\n");
}

void _2() {
    printf("start token\n");
}

void _113() {
    printf("int var type token\n");
}

void _114() {
    printf("char var type token\n");
}

void _115() {
    printf("bool var type token\n");
}

void _116() {
    printf("string var type token\n");
}

void _105() {
    printf("store token\n");
}

void _104() {
    printf("load token\n");
}

void _100() {
    printf("register token\n");
}

void _117() {
    printf("modulus token\n");
}

void _118() {
    printf("floor divide token\n");
}

void _012() {
    printf("not token\n");
}

void _013() {
    printf("equals token\n");
}

void _014() {
    printf("goto token\n");
}

void _1() {
    printf("label token\n");
}

void _210() {
    printf("== token");
}

void _211() {
    printf("= token");
}

void _119() {
    printf("end token\n");
}

void _120() {
    printf("function token\n");
}

void _121() {
    printf("return token");
}

void _212() {
    printf("!= token\n");
}

void _213() {
    printf("< token\n");
}

void _214() {
    printf("> token\n");
}

void _215() {
    printf("<= token\n");
}

void _216() {
    printf(">= token\n");
}

void _4() {
    printf("irq token\n");
}

void _5() {
    printf("nmi token\n");
}

void _6() {
    printf("end interrupt token\n");
}

FunctionMapping lookup_table[] = {
    {"201", _201},
    {"202", _202},
    {"203", _203},
    {"301", _301},
    {"204", _204},
    {"101", _101},
    {"102", _102},
    {"111", _111},
    {"112", _112},
    {"205", _205},
    {"206", _206},
    {"207", _207},
    {"103", _103},
    {"0", EOF_func},
    {"3", _3},
    {"208", _208},
    {"209", _209},
    {"2", _2},
    {"113", _113},
    {"114", _114},
    {"115", _115},
    {"116", _116},
    {"105", _105},
    {"104", _104},
    {"100", _100},
    {"117", _117},
    {"118", _118},
    {"12", _012},
    {"13", _013},
    {"14", _014},
    {"1", _1},
    {"210", _210},
    {"211", _211},
    {"119", _119},
    {"120", _120},
    {"121", _121},
    {"212", _212},
    {"213", _213},
    {"214", _214},
    {"215", _215},
    {"216", _216},
    {"4", _4},
    {"5", _5},
    {"6", _6},
};

int parse_token(FILE *input, FILE *tmp, char *buffer) {
    long buffer2;
    char *endptr;

    if (isdigit(buffer[0])) {
        buffer2 = strtol(buffer, &endptr, 10);
        for(int i = 0; i < 44; i++) {
            if (buffer2 == bleh.tokens[i]) {
                for (int j = 0; j < 44; j++) {
                    if (buffer2 == strtol(lookup_table[j].name, NULL, 10)) {
                        lookup_table[j].func();
                        break;
                    }
                }
            } else {
                continue;
            }
        }
    } else {
        return 1;
    }
    return 0;
}

int parse_parameter(FILE *input, FILE *tmp, char *buffer) {
    printf("%s", buffer);
}

int parse(char *input_file_name) {
    FILE *input = fopen(input_file_name, "r");

    output = fopen("a.obj", "w+");

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

    while(fgets(buffer, sizeof(buffer), tmp) != NULL) {
        if (strcmp(buffer, "1000\n") == 0) {
            token_segment = 1;
        } else if (strcmp(buffer, "1001\n") == 0) {
            token_segment = 0;
            parameter_segment = 1;
        } else if (token_segment == 1) {
            if (parse_token(input, tmp, buffer) != 0) {
                return 3;
            }
        } else if (parameter_segment == 1) {
            parse_parameter(input, tmp, buffer);
        }
    }

    fclose(input);
    fclose(output);
    fclose(tmp);

    return 0;
}