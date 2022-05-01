#include <stdio.h>
#include <stdarg.h>
#include "tree_print.h"

#define ENABLE_COLOR

#ifdef ENABLE_COLOR
// ANSI escape sequences
// https://stackoverflow.com/a/23657072
// https://ru.wikipedia.org/wiki/%D0%A3%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D1%8F%D1%8E%D1%89%D0%B8%D0%B5_%D0%BF%D0%BE%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D0%BE%D1%81%D1%82%D0%B8_ANSI
#define RED_COLOR       "\x1B[31m"
#define BLACK_COLOR     "\x1B[34m" // Blue because you can't see black on black
#define STRANGE_COLOR   "\x1B[35m" // Magenta using for strange(error) behavior
#define RESET           "\x1B[0m"
#endif

#define NUM_LEN 6

// wrappers of printf
// Get from https://www.cyberforum.ru/c-beginners/thread1703404.html

int vred_printf(const char* format_str, va_list vl){
#ifdef ENABLE_COLOR
    printf(RED_COLOR);
    int res = vprintf(format_str, vl);
    printf(RESET);
#else
    int res = vprintf(format_str, vl);
    printf("R");
#endif
    return res;
}
int vblack_printf(const char* format_str, va_list vl){
#ifdef ENABLE_COLOR
    printf(BLACK_COLOR);
    int res = vprintf(format_str, vl);
    printf(RESET);
#else
    int res = vprintf(format_str, vl);
    printf("B");
#endif
    return res;
}
int vstrange_printf(const char* format_str, va_list vl){
#ifdef ENABLE_COLOR
    printf(STRANGE_COLOR);
    int res = vprintf(format_str, vl);
    printf(RESET);
#else
    int res = vprintf(format_str, vl);
#endif
    return res;
}

int red_printf(const char* format_str,...){
    va_list vl;
    va_start(vl, format_str);
    int res = vred_printf(format_str, vl);
    va_end(vl);
    return res;
}
int black_printf(const char* format_str,...){
    va_list vl;
    va_start(vl, format_str);
    int res = vblack_printf(format_str, vl);
    va_end(vl);
    return res;
}
int strange_printf(const char* format_str,...){
    va_list vl;
    va_start(vl, format_str);
    int res = vstrange_printf(format_str, vl);
    va_end(vl);
    return res;
}

void show_tree(node_t* tree){
    // TODO
}

void print_tree(node_t* node) {
    //LOG(stderr, "print node %p\n", node);
    if(node != NULL) {
        //LOG(stderr," left node %p : right node %p\n",node->left, node->right);
        putchar('(');
        print_tree(node->left);
#ifdef ENABLE_COLOR
        if(node->color==RED){
            putchar(',');
            red_printf("{R:%d}", node->key);
            putchar(',');
        }else if(node->color==BLACK){
            putchar(',');
            black_printf("{B:%d}", node->key);
            putchar(',');
        }else{
            putchar(',');
            strange_printf("{?:%d}", node->key);
            putchar(',');
        }
#else
        //printf(",{%s:%d},", node->color == RED ? "R" : "B", node->key);
        if(node->color==RED){
            printf(",{R:%d},", node->key);
        }else if(node->color==BLACK){
            printf(",{B:%d},", node->key);
        }else{
            printf(",{Err%d:%d},",node->color , node->key);
        }
#endif
        print_tree(node->right);
        putchar(')');
    } else {
        putchar('_');
    }
}

node_t* node_buf[65536];
int node_buf_idx = 0;

void print_tree_no_circle(node_t* node) {
    node_buf_idx = 0;
    print_tree_no_circle_body(node);
    printf("\n");
}
    
void print_tree_no_circle_body(node_t* node) {
    int i;
    if(node == NULL) {
        putchar('_');
        return;
    }

    for(i=0; i<node_buf_idx; i++) {
        if(node_buf[i] == node) {
            printf("circle!{%c:%d}!", node->color == RED ? 'R' : 'B', node->key);
            return;
        }
    }
    node_buf[node_buf_idx++] = node;
    if(node_buf_idx > 10000) {
        fprintf(stderr, "W!\n");
        return;
    }

    if(node != NULL) {
        putchar('(');
        print_tree_no_circle_body(node->left);
        printf(",{%c:%d},", node->color == RED ? 'R' : 'B', node->key);
        print_tree_no_circle_body(node->right);
        putchar(')');
    } else {
        putchar('?');
        return;
        // impossible
    }

}
