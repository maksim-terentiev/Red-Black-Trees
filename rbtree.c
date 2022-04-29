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

void rebalance(node_t *node){ // rebalance and recolor after insert
    if(node==NULL){
        fprintf(stderr,
            "Rebalance warning : You trying to rebalance NULL pointer\n");
        return;
    }
    if(node->color==BLACK) // fine, black don't break tree
        return;
    if(father(node)==NULL){ // root, in black anyway
        node->color=BLACK;
        return;
    }
    if(father(node)->color==BLACK) // fine, nothing to do
        return;
//    if(uncle(node)==NULL){
//        fprintf("Rebalance warning : Parent is RED, but uncle doesn't exist\n"
//                "                  : Maybe corruption, maybe I misunderstand"
//                                   " trees");
//        father(node)->color=BLACK;
//        rebalance(father(node);
//    }
    if(grandpa(node)==NULL){
        fprintf(stderr,"Rebalance warning : Father is root but have RED color\n"
                       "                  : Perhaps  tree structure corrupted\n"
                       "                  : Autocorrect father color to BLACK\n"
        );
        rebalance(father(node));
    }
    if(uncle(node)!=NULL && uncle(node)->color==RED){
        father(node)->color=BLACK;
        uncle(node)->color=BLACK;
        grandpa(node)->color=RED;
        rebalance(grandpa(node));
        return;
    }
    if(node->key > father(node)->key){ // we are right leaf
        father(node)->color=BLACK;
        grandpa(node)->color=RED;
        left_rotate(father(node));
        rebalance(father(node));
    }else{ // we are left leaf
        father(node)->color=BLACK;
        grandpa(node)->color=RED;
        right_rotate(father(node));
        rebalance(father(node));
    }
}

void uinsert(node_t** tree, int key){ // Universal insert.
    if(tree==NULL){                   // Make new root if tree is empty
        fprintf(stderr,"UInsert error : Wrong call. NULL address got\n");
        fprintf(stderr,"              : Usage 'uinsert(&root,key);'\n");
        exit(1);
    }else if(*tree == NULL){ // Initiation of new tree
        *tree = new_node();
        (*tree)->key=key;
        (*tree)->color=BLACK;
    }else{
        insert(*tree,key);
    }
}

void insert(node_t* tree, int key){
    if(tree==NULL){
        fprintf(stderr,"Insert error : Insert can't be done in NULL pointer\n");
        fprintf(stderr,"             : Use uinsert instead\n");
        exit(1);
    }
    // Internal looking algorithm, maybe can be change to external function
    node_t* parent;
    while(tree!=NULL){
        parent=tree;
        if(key>tree->key){
            tree=tree->right;
        }else if(key<tree->key){
            tree=tree->left;
        }else{
            fprintf(stderr,"Insert error : Key '%d' already exist\n",key);
            exit(1);
        }
    }


    tree = new_node();
    tree->key=key;
    tree->color=RED;
    tree->parent=parent;

    if(key>parent->key)
        parent->right = tree;
    else
        parent->left = tree;

    // TODO: Add code to do red-black tree instead usual tree
    rebalance(tree);
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

void left_rotate(node_t* pivot) {
    node_t *parent, *root;
    
    parent = pivot->parent;
    if(parent == NULL) { exit(1); }
    root = parent->parent;
    
    // linking parent's right child to pivot's left child
    parent->right = pivot->left;
    if(pivot->left != NULL) {
        pivot->left->parent = parent;
    }
    
    // linking pivot to root's child
    pivot->parent = root;
    if(root != NULL) {
        if(parent == root->left) {
            root->left = pivot;
        } else {
            root->right = pivot;
        }
    }

    // linking pivot's left child to parent
    pivot->left = parent;
    parent->parent = pivot;

}

void right_rotate(node_t* pivot) {
    node_t *parent, *root;
    
    parent = pivot->parent;
    if(parent == NULL) { exit(1); }
    root = parent->parent;
    
    // linking parent's left child to pivot's right child
    parent->left = pivot->right;
    if(pivot->right != NULL) {
        pivot->right->parent = parent;
    }
    
    // linking pivot to root's child
    pivot->parent = root;
    if(root != NULL) {
        if(parent == root->left) {
            root->left = pivot;
        } else {
            root->right = pivot;
        }
    }

    // linking pivot's right child to parent
    pivot->right = parent;
    parent->parent = pivot;

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
