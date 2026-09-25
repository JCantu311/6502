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

int emit() {
    return 0;
}