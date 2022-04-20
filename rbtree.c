#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

node_t* new_node(node_t* left, int value, node_t* right) {
    node_t* ptr = malloc(sizeof(node_t));
    ptr->value = value;
    ptr->color = RED; // red by defalut
    ptr->left = left;
    ptr->right = right;
    return ptr;
} 

void free_tree(node_t* node) {
    if(node != NULL) {
        free_tree(node->left);
        free_tree(node->right);
        free(node); // release memory
    }
}

void print_tree(node_t* node) {
    if(node != NULL) {
        putchar('(');
        print_tree(node->left);
        putchar(',');
        printf("%d", node->value);
        putchar(',');
        print_tree(node->right);
        putchar(')');
    } else {
        putchar('_');
    }
}