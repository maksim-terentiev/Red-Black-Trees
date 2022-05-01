#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include "tree_print.h"

int main() {
    node_t* node=NULL;
    
    // rotate_test();

    uinsert(&node,41);
    uinsert(&node,45);
    uinsert(&node,42);
    uinsert(&node,43);
    uinsert(&node,44);
    uinsert(&node,46);
    uinsert(&node,48);
    uinsert(&node,47);

    print_tree(node);
    printf("\n"); // for terminal flushing
/*
    insert(node,44);
    print_tree(node);
    printf("\n"); // for terminal flushing
*/
    free_tree(node);
    
    return 0;
} 
