#ifndef RBTREE_H
#define RBTREE_H

typedef enum color_t {
   RED, BLACK 
} color_t;

typedef struct node_t {
    int value;
    color_t color;
    struct node_t* left;
    struct node_t* right;
} node_t;


void free_tree(node_t* node);
node_t* new_node();
void print_tree(node_t* node);


#endif
