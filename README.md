# Red–black Tree Implementation

### Definition
In computer science, a red–black tree is a kind of self-balancing binary search tree. Each node stores an extra bit representing "color" ("red" or "black"), used to ensure that the tree remains balanced during insertions and deletions.

``` C
typedef enum color_t {
   RED, BLACK 
} color_t;

typedef struct node_t {
    int key;
    int value;
    color_t color;
    struct node_t* left;
    struct node_t* right;
    struct node_t* parent;
} node_t;
```

### Properties
1. Every node is either red or black.
2. All NULL nodes are considered black.
3. A red node does not have a red child.
4. Every path from a given node to any of its descendant NULL nodes goes through the same number of black nodes.
5. The root of a tree should be black.