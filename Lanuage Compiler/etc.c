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
    #include <time.h>
    #include <unistd.h>
    #include <pthread.h>
#endif

char *strremove(char *str, const char *sub) {
    char *buffer = malloc(strlen(str) + 1);
    strcpy(buffer, str);
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = buffer;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return buffer;
}

void helpscrn() {
    printf("Usage: [options]\n");
    printf("Cykompiler v0.1\n");
    printf("Options:\n");
    printf("    --help      -h              Show help\n");
    printf("    --input     -i              Name input file (to compile)\n");
    printf("                Input file must be .cyk file extension or compilation will fail.\n");
    printf("    --output    -o              Name output file (always .s or .bin)\n");
    printf("                Output name must not have any file extension; the compiler will \nadd it for you\n");
    printf("    --type      -t              Output File Type (Assembly or Binary)\n");
    printf("                Output file type must be either 'asm' or 'bin'; if not specified,\n the default output type is 'asm'.\n");
}

int unknown_argument_error() {
    printf("Unknown argument. Aborting. \n Exit code: 1\n");
    return 1;
}

void remove_spaces(char *str) {
    int i = 0, j = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

void space_to_newline(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if(str[i] == ' ') {
            str[i] = '\n';
        }
        i++;
    }
}

int is_blank(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return 0;
        }
        line++;
    }
    return 1;
}

void rand_usleep(int min, int max) {
    int random_delay = min + rand() % (max - min + 1);
    fflush(stdout);

    usleep(random_delay);
    random_delay = 0;
}