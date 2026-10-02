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

#define TEXT_YELLOW "\x1b[33m"
#define TEXT_RESET "\x1b[0m"
#define TEXT_GREEN "\x1b[32m"
#define TEXT_RED "\x1b[31m"
#define TEXT_BLUE "\x1b[34m"

struct Tokens {
    int tokens[44];
};

struct Tokens bleh = {
    //         "if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", ".vars", ".endvars", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"
    .tokens = {201,   202,     203,  301,     204,    101,   102,   111,    112,   205,    206,      207,       103,    0,     3,          208,     209,         2,       113,   114,    115,    116,   105,     104,    100,   117,   118,     012,   013,     014,    1,       210,  211,  119,    120,        121,      212,  213, 214, 215,  216,   4,      5,      6}
};

char buffer[1024];

char buffer2[1024];

char buffer3[1024];

char inputfilebuffer[1024];

typedef int (*FuncPtr)(void);

FILE *output = NULL;

FILE *input = NULL;

bool var_space = true;

int line_number = 0;

int exit_code;

int end_of_file = 0;

int start_space = 0;

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
    return 0;
}

int _202() {
    // printf("while token\n");
    return 0;
}

int _203() {
    // printf("do token\n");
    return 0;
}

int _301() { // Print Character/string handling
    fprintf(output, "%s", buffer);\
    
    return 0;
}

int _204() {
    // printf("else token\n");
    return 0;
}

int _101() { // Addition Handling
    fprintf(output, "%s", buffer);
    for (int i = 0; i < 2; i++) {
        if(fgets(buffer, sizeof(buffer), input) == NULL && start_space == 1) {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "premature end of file, aborting \n Exit code: -1\n");
            funlockfile(stdout);
            return -1;
        }
        if(isdigit((unsigned char)buffer[0]) || isalpha((unsigned char)buffer[0])) {
            fprintf(output, "%s", buffer);
            continue;
        } else {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "unknown parameter in 'add', aborting \n Exit code: 6");
            printf(TEXT_YELLOW "Note: " TEXT_RESET "addition syntax is " TEXT_BLUE "add " TEXT_GREEN "[number or variable] " TEXT_YELLOW "[number or variable] ");
            funlockfile(stdout);
            return 6;
        }
    }
    return 0;
}

int _102() {
    fprintf(output, "%s", buffer);
    for (int i = 0; i < 2; i++) {
        if(fgets(buffer, sizeof(buffer), input) == NULL && start_space == 1) {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "premature end of file, aborting \n Exit code: -1\n");
            funlockfile(stdout);
            return -1;
        }
        if(isdigit((unsigned char)buffer[0]) || isalpha((unsigned char)buffer[0])) {
            fprintf(output, "%s", buffer);
            continue;
        } else {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "unknown parameter in 'add', aborting \n Exit code: 6");
            printf(TEXT_YELLOW "Note: " TEXT_RESET "addition syntax is " TEXT_BLUE "add " TEXT_GREEN "[number or variable] " TEXT_YELLOW "[number or variable] ");
            funlockfile(stdout);
            return 6;
        }
    }
    return 0;
}

int _111() {
    fprintf(output, "%s", buffer);
    for (int i = 0; i < 2; i++) {
        if(fgets(buffer, sizeof(buffer), input) == NULL && start_space == 1) {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "premature end of file, aborting \n Exit code: -1\n");
            funlockfile(stdout);
            return -1;
        }
        if(isdigit((unsigned char)buffer[0]) || isalpha((unsigned char)buffer[0])) {
            fprintf(output, "%s", buffer);
            continue;
        } else {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "unknown parameter in 'add', aborting \n Exit code: 6");
            printf(TEXT_YELLOW "Note: " TEXT_RESET "addition syntax is " TEXT_BLUE "add " TEXT_GREEN "[number or variable] " TEXT_YELLOW "[number or variable] ");
            funlockfile(stdout);
            return 6;
        }
    }
    return 0;
}

int _112() {
    fprintf(output, "%s", buffer);
    for (int i = 0; i < 2; i++) {
        if(fgets(buffer, sizeof(buffer), input) == NULL && start_space == 1) {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "premature end of file, aborting \n Exit code: -1\n");
            funlockfile(stdout);
            return -1;
        }
        if(isdigit((unsigned char)buffer[0]) || isalpha((unsigned char)buffer[0])) {
            fprintf(output, "%s", buffer);
            continue;
        } else {
            flockfile(stdout);
            printf(TEXT_RED "Error: " TEXT_RESET "unknown parameter in 'add', aborting \n Exit code: 6");
            printf(TEXT_YELLOW "Note: " TEXT_RESET "addition syntax is " TEXT_BLUE "add " TEXT_GREEN "[number or variable] " TEXT_YELLOW "[number or variable] ");
            funlockfile(stdout);
            return 6;
        }
    }
    return 0;
}

int _205() {
    // printf("read token\n");
    return 0;
}

int _206() {  // Variable Space Handling
    strcpy(buffer2, buffer);

    while(fgets(buffer3, sizeof(buffer3), input) != NULL && var_space == true) {
        fprintf(output, "%s", buffer3);
        if (strcmp(buffer3, "t207\n") == 0) {
            var_space = false;
            break;
        } else if (strcmp(buffer3, "t206\n") == 0) {
            continue;
        }

        char *unparsed_types[5] = {"t103\n", "t113\n", "t114\n", "t115\n", "t116\n"};

        int dif_found = 0;

        for(int i = 0; i < 5; i++) {
            if(strcmp(buffer3, unparsed_types[i]) == 0) {
                dif_found = 1;
                fgets(buffer3, sizeof(buffer3), input);
                fprintf(output, "%s", buffer3);
                fgets(buffer3, sizeof(buffer3), input);
                if(isdigit((unsigned char)buffer3[0])) {
                    fprintf(output, "%s", buffer3);
                    break;
                } else {
                    flockfile(stdout);
                    printf("No size allocated error, aborting \n Exit code: 4\n");
                    printf(TEXT_YELLOW "   Note: " TEXT_RESET "variable syntax is " TEXT_BLUE "[type] " TEXT_GREEN "[name] " TEXT_YELLOW "[allocated bytes]\n" TEXT_RESET);
                    printf(TEXT_YELLOW "   Note: " TEXT_RESET " Variable names have a maximum size of 64 bytes\n");
                    funlockfile(stdout);
                    return 4;
                }
            }
        }

        if (dif_found == 1) {
            continue;
        } else {
            flockfile(stdout);
            printf("Unknown type error in .vars, aborting \n Exit code: 3\n");
            printf("%s", buffer3);
            printf(TEXT_YELLOW "   Note: " TEXT_RESET "variable syntax is " TEXT_BLUE "[type] " TEXT_GREEN "[name] " TEXT_YELLOW "[allocated bytes]\n" TEXT_RESET);
            printf(TEXT_YELLOW "   Note: " TEXT_RESET " Variable names have a maximum size of 64 bytes\n");
            fflush(stdout);
            funlockfile(stdout);
            return 3;
        }
    }

    if (var_space == false) {
        return 0;
    }

    char token_buffer[16];

    char *types[5] = {"103\n", "113\n", "114\n", "115\n", "116\n"};
    int this_found = 0;
    for (int i = 0; i < 5; i++) {
        if(strcmp(buffer3, types[i]) == 0) {
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
        flockfile(stdout);
        printf("Syntax Error in .vars: unknown type \n Exit code %d\n", 3);
        printf("%s\n", token_buffer);
        fflush(stdout);
        funlockfile(stdout);
        return 3;
    }

    return 0;
}

int _207() {
    // printf("end variable space token\n");
    return 0;
}

int _103() {
    // printf("address var type token\n");
    return 0;
}

int EOF_func() {
    // printf("end of file token\n");
    fclose(input);
    fclose(output);
    end_of_file = 1;
    return 0;
}

int _3() {
    // printf("include token\n");
    return 0;
}

int _208() {
    // printf("endif token\n");
    return 0;
}

int _209() {
    // printf("endwhile token\n");
    return 0;
}

int _2() {
    // printf("start token\n");
    fprintf(output, "%s", buffer);
    start_space = 1;
    // while (start_space) {
    //     while(fgets(buffer, sizeof(buffer), input) != NULL) {
    //         if (strcmp(buffer, "t119\n") == 0) {
    //             start_space = 0;
    //             break;
    //         }

    //         for(int i = 0; i < 44; i++) {
    //             if(strcmp(buffer, lookup_table[i].name) == 0) {
    //                 lookup_table[i].func();
    //                 break;
    //             }
    //         }
    //     }
    // }
    return 0;
}

int _113() {
    // printf("int var type token\n");
    return 0;
}

int _114() {
    // printf("char var type token\n");
    return 0;
}

int _115() {
    // printf("bool var type token\n");
    return 0;
}

int _116() {
    // printf("string var type token\n");
    return 0;
}

int _105() {
    // printf("store token\n");
    return 0;
}

int _104() {
    // printf("load token\n");
    return 0;
}

int _100() {
    // printf("register token\n");
    return 0;
}

int _117() {
    // printf("modulus token\n");
    return 0;
}

int _118() {
    // printf("floor divide token\n");
    return 0;
}

int _012() {
    // printf("not token\n");
    return 0;
}

int _013() {
    // printf("equals token\n");
    return 0;
}

int _014() {
    // printf("goto token\n");
    return 0;
}

int _1() {
    // printf("label token\n");
    return 0;
}

int _210() {
    // printf("== token");
    return 0;
}

int _211() {
    // printf("= token");
    return 0;
}

int _119() {
    // printf("end token\n");
    fprintf(output, "%s", buffer);
    start_space = 0;
    return 0;
}

int _120() {
    // printf("function token\n");
    return 0;
}

int _121() {
    // printf("return token");
    return 0;
}

int _212() {
    // printf("!= token\n");
    return 0;
}

int _213() {
    // printf("< token\n");
    return 0;
}

int _214() {
    // printf("> token\n");
    return 0;
}

int _215() {
    // printf("<= token\n");
    return 0;
}

int _216() {
    // printf(">= token\n");
    return 0;
}

int _4() {
    // printf("irq token\n");
    return 0;
}

int _5() {
    // printf("nmi token\n");
    return 0;
}

int _6() {
    // printf("end interrupt token\n");
    return 0;
}

int parse_token() {
    long buffer2;
    char *endptr;

    int returned;

    char tmp_buf[1024]; // All buffers share this same size, don't get on my ass

    tmp_buf[0] = '\0';

    if (buffer[0] == 't' && isdigit((unsigned char)buffer[1])) {
        int len = strlen(buffer);
        for(int i = 1; i <= len; i++) {
            tmp_buf[i - 1] = buffer[i];
        }
    }
    

    if (isdigit(tmp_buf[0])) {
        buffer2 = strtol(tmp_buf, &endptr, 10);
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

int parse(char *input_file_name) {
    input = fopen(input_file_name, "r");

    output = fopen("a.obj", "w+");

    rewind(input);

    int token_segment = 0;
    int parameter_segment = 0;

    while(fgets(buffer, sizeof(buffer), input) != NULL) {
        if (end_of_file == 1) {
            return 0;
        } else if (parse_token() != 0) {
                return 3;
            }
        }

    if (end_of_file == 0) {
        fclose(input);
        fclose(output);
    }

    return 0;
}