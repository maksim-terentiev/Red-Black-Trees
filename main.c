#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"
#include "tree_print.h"

int main() {
    node_t* node=NULL;
    
    uinsert(&node,41,1);
    uinsert(&node,45,2);
    uinsert(&node,42,3);
    uinsert(&node,43,4);
    uinsert(&node,44,5);
    uinsert(&node,46,6);
    uinsert(&node,48,7);
    uinsert(&node,47,8);

    print_tree(node);
    printf("\n"); // for terminal flushing
    show_tree(node);

    free_tree(node);
    
    return 0;
} 
