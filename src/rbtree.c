#include "rbtree.h"
#include <stdlib.h>

static node_t* tree_minimum(rbtree *t, node_t *n);
static node_t* tree_maxmum(rbtree *t, node_t *n);

rbtree *new_rbtree(void) {
    rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
    // TODO: initialize struct if needed

    if (t == NULL) {
        return NULL;
    }

    node_t *nil_node = malloc(sizeof(node_t));
    if (nil_node == NULL) {
        free(t);
        return NULL;
    }

    nil_node->left = nil_node->right = nil_node->parent = nil_node;
    nil_node->color = RBTREE_BLACK;
    t->nil = nil_node;
    t->root = t->nil;

    return t;
}

void delete_rbtree(rbtree *t) {
    // TODO: reclaim the tree nodes's memory
    free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    // TODO: implement insert



    return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    // TODO: implement find
    return t->root;
}

node_t *rbtree_min(const rbtree *t) {
    // TODO: implement find
    if (t->root == t->nil) {
        return NULL;
    }
    return tree_minimum(t, t->root);
}

static node_t* tree_minimum(rbtree *t, node_t *n) {
    while (n->left != t->nil) {
        n = n->left;
    }
    return n;
}

node_t* rbtree_max(const rbtree *t) {
    // TODO: implement find
    if (t->root == t->nil) {
        return NULL;
    }
    return tree_maxmum(t, t->root);
}

static node_t* tree_maximum(rbtree *t, node_t *n) {
    while (n->right != t->nil) {
        n = n->right;
    }
    return n;
}

int rbtree_erase(rbtree *t, node_t *p) {
    // TODO: implement erase
    return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    // TODO: implement to_array
    return 0;
}