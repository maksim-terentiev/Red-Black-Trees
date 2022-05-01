#ifndef _ERR_MACRO_H
#define _ERR_MACRO_H

#include <stdio.h>
#include <stdlib.h>

//#define DEBUG
#ifdef DEBUG
    #include "tree_print.h"

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
