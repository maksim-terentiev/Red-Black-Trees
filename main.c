#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

int main() {

    node_t* node = new_node();
        node->key = 43;
        node->color=BLACK;
        node->left=new_node();
            node->left->parent=node;
            node->left->key = 41;
            node->left->color=RED;
            node->left->right = new_node();
                node->left->right->parent=node->left;
                node->left->right->key = 42;
                node->left->right->color=BLACK;
    node->right = new_node();
            node->right->parent=node;
            node->right->key = 44;
            node->right->color=RED;

    print_tree(node);
    printf("\n"); // for terminal flushing
    free_tree(node);
    
    return 0;
} 
