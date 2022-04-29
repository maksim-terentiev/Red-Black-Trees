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

void rebalance_debug(node_t *node) {
    printf("before rebalance\n");
    print_tree_no_circle(node);

    rebalance(node);

    printf("after rebalance\n");
    print_tree_no_circle(node);
}

void rebalance(node_t *node){ // rebalance and recolor after insert
    node_t *father_node, *grandpa_node, *uncle_node;
    
    ASSERT(node != NULL,
        "Rebalance warning : You trying to rebalance NULL pointer\n"
    );

    father_node = father(node);
    grandpa_node = grandpa(node);
    uncle_node = uncle(node);
    
    if(node->color == BLACK) // fine, black don't break tree
        return;
    if(father_node == NULL) { // root, in black anyway
        node->color = BLACK;
        return;
    }
    if(father_node->color == BLACK) // fine, nothing to do
        return;
    if(grandpa_node == NULL) {
        fprintf(stderr,"Rebalance warning : Father is root but have RED color\n"
                       "                  : Perhaps  tree structure corrupted\n"
                       "                  : Autocorrect father color to BLACK\n"
        );
        exit(1); // let it crush!
        //rebalance_debug(father(node));
    }

    if(uncle_node != NULL && uncle_node->color == RED){
        printf("Uncle is red! Simple!\n");
        father(node)->color=BLACK;
        uncle(node)->color=BLACK;
        grandpa(node)->color=RED;
        rebalance_debug(grandpa(node));
        return;
    }

    if(node == father(node)->right) { // we are right leaf
        printf("Is right child!\n");
        ASSERT(father_node != NULL, "father null!\n");
        ASSERT(grandpa_node != NULL, "grandpa null!\n");
        father_node->color=BLACK;
        grandpa_node->color=RED;
        left_rotate(father_node);
        rebalance_debug(father_node);
    } else if(node == father(node)->left) { // we are left leaf
        printf("Is left child!\n");
        ASSERT(father_node != NULL, "father null!\n");
        ASSERT(grandpa_node != NULL, "grandpa null!\n");
        father_node->color=BLACK;
        grandpa_node->color=RED;
        right_rotate(father_node);
        rebalance_debug(father_node);
    } else {
        PANIC("adopted child, so poor!\n");
    }    
}

void uinsert(node_t** tree, int key){ // Universal insert.
    ASSERT(tree != NULL, // Make new root if tree is empty
        "Insert error : Wrong call. NULL address got\n"
        "             : Usage 'uinsert(&root,key);'\n"
    );

    if(*tree == NULL){ // Initiation of new tree
        *tree = new_node();
        (*tree)->key=key;
        (*tree)->color=BLACK;
    }else{
        insert(*tree,key);
    }
}

void insert(node_t* tree, int key){
    ASSERT(tree != NULL, 
        "Insert error : Insert can't be done in NULL pointer\n"
        "             : Use uinsert instead\n"
    );

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
    rebalance_debug(tree);
}

node_t* father(node_t* node) {
    ASSERT(node != NULL, "null pointer!");
    return node->parent;
}

node_t* grandpa(node_t* node) {
    ASSERT(node != NULL, "null pointer!");
    if(node->parent == NULL) {
        return NULL;
    } else {
        return node->parent->parent;
    }
}

node_t* brother(node_t* node) {
    ASSERT(node != NULL, "null pointer!");
    if(node->parent == NULL) {
        return NULL;
    } else {
        if(node == node->parent->left) {
            return node->parent->right;
        } else if(node == node->parent->right) {
            return node->parent->left;
        } else {
            fprintf(
                stderr,
                "Brother error : \"Kid, you're adopted\"\n"
                "              : Parent node doesn't have pointer to current"
                /* line wrap */" node\n"
                "              : Perhaps tree structure corrupted\n"
            );
            exit(1);
        }
    }
}

node_t* uncle(node_t* node) {
    ASSERT(node != NULL, "null pointer!");
    return brother(father(node)); // make sense :)
}

void left_rotate(node_t* pivot) {
    node_t *parent, *root;
    
    parent = pivot->parent;
    ASSERT(parent != NULL,
        "Left Rotate error : Root can't be rotated\n"
    );
    ASSERT(parent->right == pivot,
        "Left Rotate error : Left child can't be left-rotated\n"
    );

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
    ASSERT(parent != NULL,
        "Right Rotate error : Root can't be rotated\n"
    );
    ASSERT(parent->left == pivot,
        "Right Rotate error : Right child can't be right-rotated\n"
    );
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


void rotate_test() {
    node_t O,L,R,LL,LR,RL,RR;
    O.parent = NULL;
    O.left = &L;
    O.right = &R;
    L.parent = &O;
    L.left = &LL;
    L.right = &LR;
    R.parent = &O;
    R.left = &RL;
    R.right = &RR;

    LL.parent = &L;
    LL.left = NULL;
    LL.right = NULL;
    LR.parent = &L;
    LR.left = NULL;
    LR.right = NULL;
    RL.parent = &R;
    RL.left = NULL;
    RL.right = NULL;
    RR.parent = &R;
    RR.left = NULL;
    RR.right = NULL;
    
    O.key = 0;
    L.key = 10;
    R.key = 11;
    LL.key = 100;
    LR.key = 101;
    RL.key = 110;
    RR.key = 111;

    printf("before test\n");
    print_tree_no_circle(&O);

    right_rotate(&L);

    printf("after test\n");
    print_tree_no_circle(&L);

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
