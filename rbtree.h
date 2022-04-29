#ifndef RBTREE_H
#define RBTREE_H
#include <stdbool.h>

#define DEBUG

#define ASSERT(cond, msg...) do { \
    if(!(cond)) { \
        fprintf(stderr, msg); \
        exit(1); \
    } \
} while(0)

#define PANIC(msg...) do { \
    fprintf(stderr, msg); \
    exit(1); \
} while(0)

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
void print_tree(node_t* node);
node_t* insert(node_t *tree,int key); // insert only in existing tree
void uinsert(node_t **tree,int key);// insert can be done in empty tree
void rebalance(node_t *node,node_t **root);// rebalance and recolor after insert
node_t* father(node_t* node);
node_t* grandpa(node_t* node);
node_t* brother(node_t* node);
node_t* uncle(node_t* node);
node_t* uleft_rotate(node_t* pivot, node_t** root);
void left_rotate(node_t* pivot);
node_t* uright_rotate(node_t* pivot,node_t** root);
void right_rotate(node_t* pivot);
node_t* tree_lookup(node_t* node, int key);
int property_test(node_t* node);

// for testing
void rotate_test();

#endif
