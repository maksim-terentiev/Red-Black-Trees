#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include "tree_print.h"

int main() {
    node_t* node=NULL;
    
    rotate_test();

    uinsert(&node, 43);
    //print_tree(node);
    //printf("\n"); // for terminal flushing

    uinsert(&node,41);
    //print_tree(node);
    //printf("\n"); // for terminal flushing

    uinsert(&node,42);
    uinsert(&node,44);
    print_tree_no_circle(node);
    printf("\n"); // for terminal flushing
/*
    insert(node,44);
    print_tree(node);
    printf("\n"); // for terminal flushing
*/
    free_tree(node);
    
    return 0;
} 
