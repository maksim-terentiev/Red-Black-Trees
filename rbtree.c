#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

node_t* new_node() {
    node_t* ptr = malloc(sizeof(node_t));
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->parent = NULL;
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
        printf(",{%c:%d},", node->color == RED ? 'R' : 'B', node->key);
        print_tree(node->right);
        putchar(')');
    } else {
        putchar('_');
    }
}


node_t* father(node_t* node) {
    return node->parent;
}

node_t* grandpa(node_t* node) {
    if(node->parent == NULL) {
        return NULL;
    } else {
        return node->parent->parent;
    }
}

node_t* brother(node_t* node) {
    if(node->parent == NULL) {
        return NULL;
    } else {
        if(node == node->parent->left) {
            return node->parent->right;
        } else if(node == node->parent->right) {
            return node->parent->left;
        } else {
            fprintf(stderr, "Impossible! Something wrong!");
            exit(1);
        }
    }
}

node_t* uncle(node_t* node) {
    return brother(father(node)); // make sense :)
}

void left_rotate(node_t* node) {
    node_t *parent, *left, *right;
    node_t *rightright, *rightleft;

    parent = node->parent;

    left = node->left;
    if(left == NULL) { exit(1); }
    right = node->right;
    


    parent->left = right;
    right->left = node;
    right->right = rightright;
    node->left = left;
    node->right = rightleft;

    // Well, this is though

    // TODO ... 



}



/*
    this function loopups a key for the corresponding node, recursively.
*/

node_t* tree_lookup(node_t* node, int key) {
    if(node == NULL) { return NULL; }

    if(node->key == key) {
        return node;
    } else if(node->key < key) {
        return tree_lookup(node->left, key);
    } else { // if(node->key > key)
        return tree_lookup(node->right, key);
    }
}

/* 
    this function test whether the tree has all five
    properties to be a "REAL" red-black tree. 
    
    returns "-1" if it doesn't have all five properties

    otherwise returns the number of black nodes, that goes
    through to every NULL nodes.
*/

int property_test(node_t* node) {
    int left_depth, right_depth;

    if(node == NULL) {
        return 0;
    }

    // prop 1: Every node is either red or black.

    // prop 2: All NULL nodes are considered black.

    // prop 3: A red node does not have a red child.

    if(node->color == RED) {
        if(node->left->color == RED
        || node->right->color == RED) {
            return -1;
        }
    }

    // prop 5: The root of a tree should be black.

    if(node->parent == NULL
    && node->color == RED) {
        return -1;
    }

    // prop 4: Every path from a given node to any of its descendant NULL nodes
    //         goes through the same number of black nodes.

    left_depth = property_test(node->left);
    if(left_depth == -1) { return -1; }

    right_depth = property_test(node->right);
    if(right_depth == -1) { return -1; }

    if(left_depth != right_depth) { return -1; }

    if(node->color == RED) {
        return left_depth;
    } else {
        return left_depth + 1;
    }
}
