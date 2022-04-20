#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

int main() {

    printf("ooooolololololo!\n");

    node_t* node = new_node(
        new_node(
            NULL,
            41,
            new_node(
                NULL,
                42,
                NULL
            )
        ),
        43,
        new_node(
            NULL,
            44,
            NULL
        )
    );

    print_tree(node);
    printf("\n"); // for terminal flushing
    free_tree(node);
    
    return 0;
} 