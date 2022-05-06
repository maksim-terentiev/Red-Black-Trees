#ifndef RBTREE_H
#define RBTREE_H
#include <stdbool.h>

typedef enum color_t {
   RED, BLACK 
} color_t;

#define KEY_TYPE int          // node->key type
#define VALUE_TYPE long int   // node->value type
#define KEY_FORMAT_STR "%d"   // format string of value and key use by show_tree
#define VALUE_FORMAT_STR "%ld"
typedef struct node_t {
    KEY_TYPE key;
    VALUE_TYPE value;
    color_t color;
    struct node_t* left;
    struct node_t* right;
    struct node_t* parent;
} node_t;

void free_tree(node_t* node);
node_t* new_node();
void uinsert(node_t **tree, KEY_TYPE key, VALUE_TYPE value);
node_t* father(node_t* node);
node_t* grandpa(node_t* node);
node_t* brother(node_t* node);
node_t* uncle(node_t* node);
bool is_left_pos(node_t* node);
bool is_right_pos(node_t* node);
node_t* tree_lookup(node_t* node, KEY_TYPE key);
int property_test(node_t* node);

// for testing
void rotate_test();

#endif
