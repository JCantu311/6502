#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "parse.h"
#include "emit.h"
#include "input.h"
#include "etc.h"
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#ifdef _WIN32
    // This is purely to help prevent errors from appearing in VS Code on non-POSIX systems (such as Windows).
    // There are currently no plans to implement any systems to allow this code to compile on non-POSIX systems.
#else 
    #include <unistd.h>
    #include <pthread.h>
#endif

struct Tokens {
    int tokens[44];
};

struct Tokens bleh = {
    //         "if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", ".vars", ".endvars", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"
    .tokens = {201,   202,     203,  301,     204,    101,   102,   111,    112,   205,    206,      207,       103,    0,     3,          208,     209,         2,       113,   114,    115,    116,   105,     104,    100,   117,   118,     012,   013,     014,    1,       210,  211,  119,    120,        121,      212,  213, 214, 215,  216,   4,      5,      6}
};

char buffer[1024];

char buffer2[1024];

typedef int (*FuncPtr)(void);

FILE *output = NULL;

FILE *input = NULL;

FILE *tmp = NULL;

int line_number = 0;

int exit_code;

int end_of_file = 0;

typedef struct {
    const char *name;
    FuncPtr func;
} FunctionMapping;

unsigned long parameter_index;

unsigned long previous_location;

int _201();
int _202();
int _203();
int _301();
int _204();
int _101();
int _102();
int _111();
int _112();
int _205();
int _206();
int _207();
int _103();
int EOF_func();
int _3();
int _208();
int _209();
int _2();
int _113();
int _114();
int _115();
int _116();
int _105();
int _104();
int _100();
int _117();
int _118();
int _012();
int _013();
int _014();
int _1();
int _210();
int _211();
int _119();
int _120();
int _121();
int _212();
int _213();
int _214();
int _215();
int _216();
int _4();
int _5();
int _6();

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

int _201() {
    // printf("if token\n");
}

int _202() {
    // printf("while token\n");
}

int _203() {
    // printf("do token\n");
}

int _301() {
    // printf("print token\n");
}

int _204() {
    // printf("else token\n");
}

int _101() {
    // printf("add token\n");
}

int _102() {
    // printf("subtract token\n");
}

int _111() {
    // printf("multiply token\n");
}

int _112() {
    // printf("divide token\n");
}

int _205() {
    // printf("read token\n");
}

int _206() {
    strcpy(buffer2, buffer);
    fgets(buffer, sizeof(buffer), tmp);
    char token_buffer[16];

    char *types[5] = {"103\n", "113\n", "114\n", "115\n", "116\n"};
    int this_found = 0;
    for (int i = 0; i < 5; i++) {
        if(strcmp(buffer, types[i]) == 0) {
            strcpy(token_buffer, types[i]);
            this_found = 1;
        }
    }

    if (this_found == 1) {
        for (int j = 0; j < 44; j++) {
            if (strtol(token_buffer, NULL, 10) == strtol(lookup_table[j].name, NULL, 10)) {
                lookup_table[j].func();
                break;
            }
        }
    } else {
        printf("Syntax Error in .vars: unknown type \n Exit code %d\n", 3);
        fflush(stdout);
        return 3;
    }

    previous_location = ftell(tmp);



    return 0;
}

int _207() {
    // printf("end variable space token\n");
}

int _103() {
    // printf("address var type token\n");
}

int EOF_func() {
    // printf("end of file token\n");
    fclose(tmp);
    fclose(input);
    fclose(output);
    end_of_file = 1;
}

int _3() {
    // printf("include token\n");
}

int _208() {
    // printf("endif token\n");
}

int _209() {
    // printf("endwhile token\n");
}

int _2() {
    // printf("start token\n");
}

int _113() {
    // printf("int var type token\n");
}

int _114() {
    // printf("char var type token\n");
}

int _115() {
    // printf("bool var type token\n");
}

int _116() {
    // printf("string var type token\n");
}

int _105() {
    // printf("store token\n");
}

int _104() {
    // printf("load token\n");
}

int _100() {
    // printf("register token\n");
}

int _117() {
    // printf("modulus token\n");
}

int _118() {
    // printf("floor divide token\n");
}

int _012() {
    // printf("not token\n");
}

int _013() {
    // printf("equals token\n");
}

int _014() {
    // printf("goto token\n");
}

int _1() {
    // printf("label token\n");
}

int _210() {
    // printf("== token");
}

int _211() {
    // printf("= token");
}

int _119() {
    // printf("end token\n");
}

int _120() {
    // printf("function token\n");
}

int _121() {
    // printf("return token");
}

int _212() {
    // printf("!= token\n");
}

int _213() {
    // printf("< token\n");
}

int _214() {
    // printf("> token\n");
}

int _215() {
    // printf("<= token\n");
}

int _216() {
    // printf(">= token\n");
}

int _4() {
    // printf("irq token\n");
}

int _5() {
    // printf("nmi token\n");
}

int _6() {
    // printf("end interrupt token\n");
}

int parse_token(FILE *input, FILE *tmp, char *buffer) {
    long buffer2;
    char *endptr;

    int returned;

    if (isdigit(buffer[0])) {
        buffer2 = strtol(buffer, &endptr, 10);
        for(int i = 0; i < 44; i++) {
            if (buffer2 == bleh.tokens[i]) {
                for (int j = 0; j < 44; j++) {
                    if (buffer2 == strtol(lookup_table[j].name, NULL, 10)) {
                        returned = lookup_table[j].func();
                        if (returned != 0) {
                            return returned;
                        }
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
    // printf("%s", buffer);
}

int parse(char *input_file_name) {
    input = fopen(input_file_name, "r");

    output = fopen("a.obj", "w+");

    tmp = fopen("a.txt", "w+");

    fprintf(tmp, "1000\n");

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if ((buffer[0] == 't') && isdigit(buffer[1])) {
            fprintf(tmp, "%s", &buffer[1]);
        } 
    }

    rewind(input);

    fprintf(tmp, "1001\n");

    parameter_index = ftell(tmp);

    // printf("%lu\n", parameter_index);

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if (buffer[0] != 't' || (buffer[0] == 't') && !isdigit(buffer[1])) {
            fprintf(tmp, "%s", buffer);
        } 
    }

    rewind(tmp);

    int token_segment = 0;
    int parameter_segment = 0;

    while(fgets(buffer, sizeof(buffer), tmp) != NULL) {
        if (end_of_file == 1) {
            return 0;
        }
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

    if (end_of_file == 0) {
        fclose(input);
        fclose(output);
        fclose(tmp);
    }

    return 0;
}