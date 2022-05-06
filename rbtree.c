#include <stdlib.h>
#include "err_macro.h"
#include "rbtree.h"

// Internal functions
            // insert only in existing tree
static node_t* insert(node_t *tree,KEY_TYPE key,VALUE_TYPE value);
static void left_rotate(node_t* pivot);
static void right_rotate(node_t* pivot);
static void rebalance(node_t *node,node_t **root);// rebalance and recolor after insert
static void rotate(node_t* pivot, node_t** root);

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

void rebalance(node_t *node, node_t **root)  // rebalance and recolor after
{                                            // insert
    node_t *father_node, *grandpa_node, *uncle_node;

#ifdef DEBUG
    // Debug printing : pre
    LOG("Rebalance node(%p), root(%p) : started\n",node,*root);
    LOG("root(%p) : Before rebalance\n",*root);
    print_tree(*root); putchar('\n');
    LOG("with node(%p)\n",node);
    LOG("     subtree node(%p): ",node);
    print_tree(node); putchar('\n');
#endif

    ASSERT(node == NULL,
        "Rebalance error : You trying to rebalance NULL pointer\n"
    );

    father_node = father(node);
    grandpa_node = grandpa(node);
    uncle_node = uncle(node);
    
    if(node->color == BLACK) // fine, black don't break tree
    {
        LOG("Rebalance: node(%p) is black, no actions required\n",node);
        return;
    }
    if(father_node == NULL) // root, in black anyway
    { 
        LOG("Rebalance: node(%p)->parent is root, in black anyway\n",node);
        node->color = BLACK;
        return;
    }
    if(father_node->color == BLACK) // fine, nothing to do
    {
        LOG("Rebalance: node(%p)->parent is black, no actions required\n",node);
        return;
    }
    
    ASSERT(grandpa_node == NULL,
        "Rebalance warning : Father is root but have RED color\n"
        "                  : Perhaps  tree structure corrupted\n"
        "                  : Halt program\n"
    );

    if(uncle_node != NULL && uncle_node->color == RED) {
        LOG("Rebalance: node(%p)'s uncle is red, simple\n",node);
        father_node->color=BLACK;
        uncle_node->color=BLACK;
        grandpa_node->color=RED;
        rebalance(grandpa_node,root);
        return;
    }

    // if father and son are not on the same side
    if(is_left_pos(father_node) ^ is_left_pos(node)) {
        LOG("Rebalance : Different Side!\n");
        // rotate son to put them on the same side
        rotate(node,root);
        node->color=BLACK;
        grandpa_node->color=RED;
        rotate(node,root);
        rebalance(node,root);
    } else {
        LOG("Rebalance : Same Side!\n");
        father_node->color=BLACK;
        grandpa_node->color=RED;
        rotate(father_node,root);
        rebalance(father_node,root);
    }

#ifdef DEBUG
// Debug printing : after
    LOG("root(%p) : after rebalance\n",root);
    print_tree(*root); putchar('\n');
    LOG("Rebalance node(%p), root(%p) : ended\n",node,*root);
#endif
}

bool key_less(KEY_TYPE a, KEY_TYPE b) // cmp keys: a<b // if not int type
{
    // for int
    return a<b;
}
bool key_great(KEY_TYPE a, KEY_TYPE b) // cmp keys: a>b // if not int type
{
    // for int
    return a>b;
}
void uinsert(node_t** tree, KEY_TYPE key,VALUE_TYPE value)
    // Universal insert.
    // Make new root if tree is empty
{
    ASSERT(tree == NULL,
        "Insert error : Wrong call. NULL address got\n"
        "             : Usage 'uinsert(&root,key);'\n"
    );
#ifdef DEBUG
    LOG("Uinsert : start\n");
    LOG("Before insert:\n");
    print_tree(*tree); putchar('\n');
#endif
    if(*tree == NULL){ // Initiation of new tree
        *tree = new_node();
        (*tree)->key=key;
        (*tree)->color=BLACK;
        (*tree)->value=value;
    }else{
        rebalance(insert(*tree,key,value), tree);
        ASSERT(property_test(*tree) == -1,
            "UInsert : Property test failed!\n"
        );
    }
#ifdef DEBUG
    LOG("Uinsert : ended\n");
    LOG("After insert:\n");
    print_tree(*tree); putchar('\n');
#endif
}

node_t* insert(node_t* tree, KEY_TYPE key,VALUE_TYPE value){ // Internal insert. Return inserted node
    ASSERT(tree == NULL, 
        "Insert error : Insert can't be done in NULL pointer\n"
        "             : Use uinsert instead\n"
    );

    // Internal looking algorithm, maybe can be change to external function
    node_t* parent;
    while(tree!=NULL){
        parent=tree;
        if(key_great(key, tree->key)){
            tree=tree->right;
        }else if(key_less(key, tree->key)){
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
    tree->value=value;

    if(key_great(key, parent->key))
        parent->right = tree;
    else
        parent->left = tree;

    return tree;
}

node_t* father(node_t* node) {
    ASSERT(node == NULL, "Father error : NULL pointer got\n");
    return node->parent;
}

node_t* grandpa(node_t* node) {
    ASSERT(node == NULL, "Grandpa error : NULL pointer got\n");
    if(node->parent == NULL) {
        return NULL;
    } else {
        return node->parent->parent;
    }
}

node_t* brother(node_t* node) {
    ASSERT(node == NULL, "Brother error : NULL pointer got\n");
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
    node_t* father_node;
    ASSERT(node == NULL, "Uncle error : NULL pointer got\n");
    father_node = father(node);

    if(father_node == NULL) {
        return NULL;
    } else {
        return brother(father_node); // make sense :)
    }
}

bool is_left_pos(node_t* node) {
    node_t* father_node;
    ASSERT(node == NULL, "is_left_pos error : NULL pointer got\n");
    father_node = father(node);
    ASSERT(father_node == NULL, "is_left_pos error : node(%p) is root\n",node);
    if(node == father_node->left) {
        return true;
    } else if(node == father_node->right) {
        return false;
    } else {
        PANIC("is_left_pos error: adopted child(%p), so poor!\n",node);
    }
}
bool is_right_pos(node_t* node){
    return !is_left_pos(node);
}

void rotate(node_t* pivot, node_t** root) {    
#ifdef DEBUG
    LOG("Rotate pivot(%p) root(%p)\n",pivot, *root);
    LOG("before rotate:\n");
    print_tree(father(pivot)); putchar('\n');
#endif

    if(is_left_pos(pivot)) {
        LOG("rotating right!\n");
        right_rotate(pivot);
        if(pivot->right == *root) {
            *root = pivot; // update root if changed
        }
    } else {
        LOG("rotating left!\n");
        left_rotate(pivot);
        if(pivot->left == *root) {
            *root = pivot; // update root if changed
        }
    }
#ifdef DEBUG
    LOG("after rotate:\n");
    print_tree(pivot); putchar('\n');
#endif
}

void left_rotate(node_t* pivot) {
    node_t *parent, *root;
    
    parent = pivot->parent;
    ASSERT(parent == NULL,
        "Left Rotate error : pivot's father is NULL\n"
    );
    ASSERT(parent->right != pivot,
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
    ASSERT(parent == NULL,
        "Right Rotate error : pivot's father is NULL\n"
    );
    ASSERT(parent->right == pivot,
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
    print_tree(&O); putchar('\n');

    right_rotate(&L);

    printf("after test\n");
    print_tree(&L); putchar('\n');

}


/*
    this function loopups a key for the corresponding node, recursively.
*/

node_t* tree_lookup(node_t* node, int key) {
    if(node == NULL) { return NULL; }

    if(node->key == key) {
        return node;
    } else if(key < node->key ) {
        return tree_lookup(node->left, key);
    } else { // if(key > node->key)
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
        return 1;
    }

    // prop 1: Every node is either red or black.

    // prop 2: All NULL nodes are considered black.

    // prop 3: A red node does not have a red child.

    if(node->color == RED) {
        if(node->left != NULL && node->left->color == RED) {
            return -1;
        }
        if(node->right != NULL && node->right->color == RED) {
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
