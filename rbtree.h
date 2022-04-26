#ifndef RBTREE_H
#define RBTREE_H
#include <stdbool.h>

typedef enum color_t {
   RED, BLACK 
} color_t;

typedef struct node_t {
    int key;
    int value;
    color_t color;
    struct node_t* left;
    struct node_t* right;
    struct node_t* parent;
} node_t;


void free_tree(node_t* node);
node_t* new_node();


#endif
