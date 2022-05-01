#ifndef RBTREE_H
#define RBTREE_H
#include <stdbool.h>

#define DEBUG

#ifdef DEBUG

    #define LOG(file,msg...) do { \
        fprintf(file,msg); \
    } while(0)

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

#else

    #define LOG(file,msg...) do {} while(1)
    #define ASSERT(cond,msg...) do {} while(1)
    #define PANIC(msg...) do {} while(1)

#endif

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
node_t* insert(node_t *tree,int key); // insert only in existing tree
void uinsert(node_t **tree,int key);// insert can be done in empty tree
void rebalance(node_t *node,node_t **root);// rebalance and recolor after insert
node_t* father(node_t* node);
node_t* grandpa(node_t* node);
node_t* brother(node_t* node);
node_t* uncle(node_t* node);
bool is_left_pos(node_t* node);
void rotate(node_t* pivot, node_t** root);
void left_rotate(node_t* pivot);
void right_rotate(node_t* pivot);
// node_t* uleft_rotate(node_t* pivot, node_t** root);
// node_t* uright_rotate(node_t* pivot,node_t** root);
node_t* tree_lookup(node_t* node, int key);
int property_test(node_t* node);

// for testing
void rotate_test();

#endif
