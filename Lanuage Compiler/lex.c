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
    char *names[44];
    int tokens[44];
};

int lex(char *inputs[], int size) {
    struct Tokens bleh = {
        .names = {"if", "while", "do", "print", "else", "add", "sub", "mult", "div", "read", "output", "input", "addr", "EOF", ".include", "endif", "endwhile", ".start", "int", "char", "bool", "str", "store", "load", "reg", "mod", "floor", "not", "equal", "goto", "label", "==", "=", ".end", ".function", "return", "!=", "<", ">", "<=", ">=", ".irq", ".nmi", ".endinterrupt"},
        .tokens = {201, 202, 203, 301, 204, 101, 102, 111, 112, 205, 206, 207, 103, -1, 3, 208, 209, 2, 113, 114, 115, 116, 103, 104, 011, 117, 118, 012, 013, 014, 1, 210, 211, 119, 120, 121, 212, 213, 214, 215, 216, 4, 5, 6}
    };
    
    FILE *input_file = fopen(inputs[4], "r");
    char buffer[1024];
    char buffer2[512];
    FILE *tmp_buffer = fopen("tmp.o", "w+");
    FILE *outfile = fopen("a.o", "w");

    if (input_file == NULL) {
        printf("File access error. Aborting \n");
        return 2;
    }

    while (fgets(buffer, sizeof(buffer), input_file) != NULL) {
        space_to_newline(buffer);
        fprintf(tmp_buffer, "%s", buffer);
    }

    rewind(tmp_buffer);
    while (fgets(buffer2, sizeof(buffer2), tmp_buffer) != NULL) {
        buffer2[strcspn(buffer2, "\n")] = '\0';

        if(buffer2[0] == '\0') {
            fprintf(outfile, "\n");
            continue;
        } else if(buffer2[0] == '\n') {
            fprintf(outfile, "\0");
        }

        int found = 0;
        for (int i = 0; i < 44; i++) {
            if (bleh.names[i] == NULL) {
                break;
            }

            if (strcmp(bleh.names[i], buffer2) == 0) {
                fprintf(outfile, "t%d\n", bleh.tokens[i]);
                found = 1;
                break;
            }
        }

        if (!found) {
            fprintf(outfile, "%s\n", buffer2);
        }
    }

    fclose(input_file);
    fclose(tmp_buffer);
    fclose(outfile);
    tmp_buffer = fopen("tmp.o", "w+");
    outfile = fopen("a.o", "r+");

    while (1) {
        memset(buffer2, 0, sizeof(buffer2));

        if (fgets(buffer2, sizeof(buffer2), outfile) == NULL) {
            break;
        }

        buffer2[strcspn(buffer2, "\r\n")] = '\0';

        if (!is_blank(buffer2)) {
            fprintf(tmp_buffer, "%s\n", buffer2);
        }
    }

    fclose(tmp_buffer);
    fclose(outfile);

    remove("a.o");
    rename("tmp.o", "a.o");

    return 0;
}