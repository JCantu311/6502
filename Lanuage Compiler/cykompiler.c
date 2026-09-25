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

volatile bool keep_spinning = true;

void* spinner_thread_func(void* arg) {
    char spinner[] = {'|', '/', '-', '\\'};
    int num_chars = sizeof(spinner) / sizeof(spinner[0]);
    int i = 0;

    printf("\e[?25l"); 

    while (keep_spinning) {
        printf("\rProcessing... %c", spinner[i % num_chars]);
        fflush(stdout);
        i++;
        usleep(100000);
    }

    printf("\rProcessing... Done!\n");
    printf("\e[?25h"); 
    fflush(stdout);

    return NULL;
}

// struct timespec {
//     time_t tv_sec;
//     long tv_nsec;
// };

int main(int argc, char *argv[]) {
    srand(time(NULL));

    #ifdef _WIN32
        // Nothing
    #else
        pthread_t spinner_thread;
    #endif

    if (argc > 7) {
        printf("Too many arguments, aborted. \n Exit code: 1\n");
        rand_usleep(250000, 999999);
        return 1;
    } else if (argc < 2) {
    no_args:
        printf("Usage: [options]\n");
        printf("Options:\n");
        printf("    --help      -h              Show help\n");
        printf("    --input     -i              Name input file (to compile)\n");
        printf("    --output    -o              Name output file (always .s or .bin)\n");
        printf("    --type      -t              Output File Type (Assembly or Binary)\n");
        return 1;
    }

    char *inputs_buffered[7] = {NULL};

    char *inputs[8] = {NULL};

    int input_flag = -1;

    int help_flag = -1;

    int output_flag = -1;

    int type_flag = -1;

    for(int i = 0; i < argc; i++) {
        inputs_buffered[i] = argv[i];
    }

    for(int i = 0; i < 6; i++) {
        inputs[i] = inputs_buffered[i + 1];
    }

    if (inputs[0] == NULL) {
        goto no_args;
    } else if (strcmp(inputs[0], "-h") != 0 && strcmp(inputs[0], "--help") != 0 && strcmp(inputs[0], "-i") != 0 && strcmp(inputs[0], "--input") != 0) {
        unknown_argument_error();
        return 1;
    } else if (strcmp(inputs[0], "--help") == 0 || strcmp(inputs[0], "-h") == 0) {
        helpscrn();
        return 1;
    } else if (inputs[0] != NULL && inputs[1] != NULL) {
        input_flag = (strcmp(inputs[0], "--input") == 0 || strcmp(inputs[0], "-i") == 0);
    } else if (inputs[0] != NULL && inputs[1] == NULL) {
        printf("No input file, aborting. \n Exit code: 1\n");
        rand_usleep(250000, 999999);
        return 1;
    }

    if (inputs[2] == NULL) {
        goto no_output;
    } else if (strcmp(inputs[2], "-o") != 0 && strcmp(inputs[2], "--output") != 0) {
        unknown_argument_error();
        return 1;
    } else if (inputs[2] != NULL && inputs[3] != NULL) {
        int output_flag = (strcmp(inputs[2], "--output") == 0 || strcmp(inputs[2], "-o") == 0);
    } else if (inputs[2] != NULL && inputs[3] == NULL) {
        printf("No output name specified, assigning default value.\n");
        rand_usleep(250000, 999999);
        int output_flag = (strcmp(inputs[2], "--output") == 0 || strcmp(inputs[2], "-o") == 0);
    }

    if (inputs[4] == NULL) {
        printf("No output type specified, assigning default value.\n");
        rand_usleep(250000, 999999);
        inputs[7] = ".s";
    } else if ((inputs[4] != NULL) && (output_flag != -1)) {
        int type_flag = (strcmp(inputs[4], "--type") == 0 || strcmp(inputs[4], "-t") == 0);
    } else if (strcmp(inputs[4], "-t") != 0 && strcmp(inputs[4], "--type") != 0) {
        unknown_argument_error();
        return 1;
    }

    if ((input_flag == 1) && (inputs[1] == NULL)) {
    no_input:
        printf("No input file specified, aborting. \n Exit code: 1\n");
        rand_usleep(250000, 999999);
        return 1;
    } else if ((input_flag != 1) && (help_flag == 1)) {
        helpscrn();
    }

no_output:
    char *file_extension = ".cyk"; 
    char *file_name;
    char *file_type;

    if (input_flag != 1 && help_flag != 1) {
        unknown_argument_error();
        return 1;
    }

    if (output_flag != -1 && output_flag != 1){
        unknown_argument_error();
        return 1;
    }

    if (type_flag != -1 && type_flag != 1) {
        unknown_argument_error();
        return 1;
    }
    
    if (inputs[1] == NULL) {
        printf("No input file specified, aborting. \n Exit code: 2\n");
        rand_usleep(250000, 999999);
        return 2;
    } else if (inputs[1] != NULL && inputs[3] == NULL) {
        inputs[6] = strremove(inputs[1], file_extension);
    } else if (inputs[3] != NULL) {
        inputs[6] = inputs[3];
    }

    if(output_flag == 1 && inputs[3] != NULL) {
        file_name = inputs[3];
        file_name = inputs[6];
    } else if (inputs[3] == NULL) {
        printf("No output specified, assigning default:\n %s\n", inputs[6]);
        rand_usleep(250000, 999999);
    }

    if(type_flag == 1 && inputs[5] != NULL) {
        file_type = inputs[5];
    }

    output_type:
    if (inputs[5] == NULL) {
        printf("No output type specified, assigning default value: \n .s\n");
        rand_usleep(250000, 999999);
        inputs[5] = "asm";
        goto output_type;
    } else if(strcmp(inputs[5], "bin")) {
        inputs[7] = ".bin";
    } else if (strcmp(inputs[5], "asm")) {
        inputs[7] = ".s";
    }

    char *inputs_fin[5] = {NULL};

    if(inputs[1] != NULL) {
        inputs_fin[0] = inputs[1];
    }

    if(inputs[6] != NULL) {
        inputs_fin[1] = inputs[6];
    }

    if(inputs[5] != NULL) {
        inputs_fin[2] = inputs[5];
    }

    if(inputs[7] != NULL) {
        inputs_fin[3] = inputs[7];
    }

    if (strcmp(inputs[5], "asm") == 0) {
        inputs_fin[3] = ".s";
    } else if (strcmp(inputs[5], "bin") == 0) {
        inputs_fin[3] = ".bin";
    }

    #ifdef _WIN32
        // Nothing
    #else
        if(pthread_create(&spinner_thread, NULL, spinner_thread_func, NULL) != 0) {
            printf("Error creating thread\n");
            rand_usleep(250000, 999999);
            return 1;
        }
    #endif

    struct timespec req;
    struct timespec rem;

    req.tv_sec = (rand() % (5 - 3 + 1)) + 3;
    req.tv_nsec = (rand() % 500000000 - 250000000 + 1) + 250000000;

    nanosleep(&req, &rem);

    char dir[4352];

    inputs_fin[4] = strcat(strcat(getcwd(dir, sizeof(dir)), "/"), inputs_fin[0]); 

    int lex_success = lex(inputs_fin, 5);

    if (lex_success == 0) {
        // printf("Lexer status: successful.\n");
    } else {
        printf("Lexer status: failure.\n Exit code: %d\n", lex_success);
        rand_usleep(250000, 999999);
        return lex_success;
    }

    int parse_success = parse("a.o");
    if (parse_success == 0) {
        // printf("Parser status: successful.\n");
    } else {
        printf("Parser status: failure.\n Exit code: %d\n", parse_success);
        rand_usleep(250000, 999999);
    }

    int emit_success = emit();
    if (emit_success == 0) {
        // printf("Emit status: successful.\n");
    } else {
        printf("Emit status: failure. \n Exit code: %d\n", emit_success);
        rand_usleep(250000, 999999);
    }

    keep_spinning = false;

    #ifdef _WIN32
        // Nothing
    #else
        pthread_join(spinner_thread, NULL);
    #endif

    printf("Successfully Compiled\n");
    rand_usleep(250000, 999999);

    printf("Cleaning up...\n");
    rand_usleep(250000, 999999);

    return 0;
}