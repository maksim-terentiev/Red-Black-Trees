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
void uinsert(node_t **tree,int key,int value);//insert can be done in empty tree
void rebalance(node_t *node,node_t **root);// rebalance and recolor after insert
node_t* father(node_t* node);
node_t* grandpa(node_t* node);
node_t* brother(node_t* node);
node_t* uncle(node_t* node);
bool is_left_pos(node_t* node);
bool is_right_pos(node_t* node);
void rotate(node_t* pivot, node_t** root);
node_t* tree_lookup(node_t* node, int key);
int property_test(node_t* node);

// for testing
void rotate_test();

#endif
