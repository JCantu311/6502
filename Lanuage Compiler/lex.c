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

struct Tokens {
    char *names[20];
    char *tokens[20];
};

int lex(char *inputs[], int size) {
    struct Tokens bleh = {
        .names = {"if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", "output", "input", "addr", EOF, ".include", "endif", "endwhile", ""},
        .tokens = {201, 202, 203, 301, 204, 101, 102, 111, 112, 205, 206, 207, 103, -1, 302, 208, 209, }
    };
    for(int i = 0; i < size; i++) {
        printf("%s\n", inputs[i] ? inputs[i] : "NULL");
    }

    FILE *input_file = fopen(inputs[4], "r");
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        
        printf("%s", buffer);
    }
    printf("\n");

    fclose(input_file);

    return 0;
}