#ifndef _ERR_MACRO_H

#ifndef _STDIO_H
#include <stdio.h>
#endif

//#define DEBUG
#ifdef DEBUG

    #ifndef _PRINTING_H_
    #include "tree_print.h"
    #endif

    #define LOG(msg...) do { \
        fprintf(stderr,msg); \
    } while(0)
#else
    #define LOG(file,msg...) do {} while(0)
    #define print_tree(...) do {} while(0)
#endif

#define ASSERT(cond, msg...) do { \
    if(cond) { \
        fprintf(stderr, msg); \
        exit(1); \
    } \
} while(0)

#define PANIC(msg...) do { \
    fprintf(stderr, msg); \
    exit(1); \
} while(0)

#endif
