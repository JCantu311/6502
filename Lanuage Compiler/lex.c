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
    char *names[31];
    int tokens[31];
};

int lex(char *inputs[], int size) {
    struct Tokens bleh = {
        .names = {"if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", "output", "input", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label"},
        .tokens = {201, 202, 203, 301, 204, 101, 102, 111, 112, 205, 206, 207, 103, -1, 302, 208, 209, 010, 113, 114, 115, 116, 103, 104, 011, 113, 114, 012, 013, 014, 1}
    };
    for(int i = 0; i < size; i++) {
        printf("%s\n", inputs[i] ? inputs[i] : "NULL");
    }

    FILE *input_file = fopen(inputs[4], "r");
    char buffer[1024];
    char buffer2[512];
    FILE *tmp_buffer = fopen("tmp.o", "w+");
    FILE *outfile = fopen("a.o", "w");

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        space_to_newline(buffer);
        fprintf(tmp_buffer, "%s", buffer);
    }
    while (fgets(buffer2, sizeof(buffer2), tmp_buffer) != NULL) {
        for(int i = 0; i < 30; i++) {
            if(bleh.names[i] == NULL) {
                break;
            } else if(strcmp(bleh.names[i], buffer2) == 0) {
                fprintf(outfile, "%d", bleh.tokens[i]);
            } else {
                fprintf(outfile, "%s", buffer2);
            }
        }
    }

    fclose(input_file);
    fclose(tmp_buffer);
    fclose(outfile);

    return 0;
}