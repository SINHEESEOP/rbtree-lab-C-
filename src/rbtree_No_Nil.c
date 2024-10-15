// #include "rbtree.h"
// #include <stdlib.h>
//
// static void rbtree_delete_node(rbtree *t, node_t *node);
// static void left_rotate(rbtree *t, node_t *x);
// static void right_rotate(rbtree *t, node_t *x);
// static void rbtree_insert_fixup(rbtree *t, node_t *z);
// static node_t *tree_minimum(node_t *x);
// static node_t *tree_maximum(node_t *x);
// static void rb_transplant(rbtree *t, node_t *u, node_t *v);
// static void rb_delete_fixup(rbtree *t, node_t *x);
// static int inorder_traversal(node_t *x, key_t *arr, int *i, const size_t n);
//
// rbtree *new_rbtree(void) {
//   rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
//   t->root = NULL; // root는 NULL로 초기화
//   return t;
// }
//
// void delete_rbtree(rbtree *t) {
//   if (t != NULL) {
//     rbtree_delete_node(t, t->root);
//     free(t);
//   }
// }
//
// static void rbtree_delete_node(rbtree *t, node_t *node) {
//   if (node != NULL) {
//     rbtree_delete_node(t, node->left);
//     rbtree_delete_node(t, node->right);
//     free(node);
//   }
// }
//
// static void left_rotate(rbtree *t, node_t *x) {
//   node_t *y = x->right;
//   x->right = y->left;
//   if (y->left != NULL) {
//     y->left->parent = x;
//   }
//   y->parent = x->parent;
//   if (x->parent == NULL) {
//     t->root = y;
//   } else if (x == x->parent->left) {
//     x->parent->left = y;
//   } else {
//     x->parent->right = y;
//   }
//   y->left = x;
//   x->parent = y;
// }
//
// static void right_rotate(rbtree *t, node_t *x) {
//   node_t *y = x->left;
//   x->left = y->right;
//   if (y->right != NULL) {
//     y->right->parent = x;
//   }
//   y->parent = x->parent;
//   if (x->parent == NULL) {
//     t->root = y;
//   } else if (x == x->parent->right) {
//     x->parent->right = y;
//   } else {
//     x->parent->left = y;
//   }
//   y->right = x;
//   x->parent = y;
// }
//
// node_t *rbtree_insert(rbtree *t, const key_t key) {
//   node_t *z = (node_t *)malloc(sizeof(node_t));
//   z->key = key;
//   z->left = z->right = z->parent = NULL;
//   z->color = RBTREE_RED;
//
//   node_t *y = NULL;
//   node_t *x = t->root;
//
//   while (x != NULL) {
//     y = x;
//     if (key < x->key) {
//       x = x->left;
//     } else {
//       x = x->right;
//     }
//   }
//
//   z->parent = y;
//   if (y == NULL) {
//     t->root = z;
//   } else if (key < y->key) {
//     y->left = z;
//   } else {
//     y->right = z;
//   }
//
//   rbtree_insert_fixup(t, z);
//   return z;
// }
//
// static void rbtree_insert_fixup(rbtree *t, node_t *z) {
//   while (z->parent != NULL && z->parent->color == RBTREE_RED) {
//     if (z->parent == z->parent->parent->left) {
//       node_t *y = z->parent->parent->right;
//       if (y != NULL && y->color == RBTREE_RED) {
//         z->parent->color = RBTREE_BLACK;
//         y->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         z = z->parent->parent;
//       } else {
//         if (z == z->parent->right) {
//           z = z->parent;
//           left_rotate(t, z);
//         }
//         z->parent->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         right_rotate(t, z->parent->parent);
//       }
//     } else {
//       node_t *y = z->parent->parent->left;
//       if (y != NULL && y->color == RBTREE_RED) {
//         z->parent->color = RBTREE_BLACK;
//         y->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         z = z->parent->parent;
//       } else {
//         if (z == z->parent->left) {
//           z = z->parent;
//           right_rotate(t, z);
//         }
//         z->parent->color = RBTREE_BLACK;
//         z->parent->parent->color = RBTREE_RED;
//         left_rotate(t, z->parent->parent);
//       }
//     }
//   }
//   t->root->color = RBTREE_BLACK;
// }
//
// node_t *rbtree_find(const rbtree *t, const key_t key) {
//   node_t *x = t->root;
//   while (x != NULL) {
//     if (key == x->key) {
//       return x;
//     } else if (key < x->key) {
//       x = x->left;
//     } else {
//       x = x->right;
//     }
//   }
//   return NULL;
// }
//
// node_t *rbtree_min(const rbtree *t) {
//   return tree_minimum(t->root);
// }
//
// static node_t *tree_minimum(node_t *x) {
//   while (x->left != NULL) {
//     x = x->left;
//   }
//   return x;
// }
//
// node_t *rbtree_max(const rbtree *t) {
//   return tree_maximum(t->root);
// }
//
// static node_t *tree_maximum(node_t *x) {
//   while (x->right != NULL) {
//     x = x->right;
//   }
//   return x;
// }
//
// int rbtree_erase(rbtree *t, node_t *z) {
//   node_t *y = z;
//   node_t *x;
//   color_t y_original_color = y->color;
//
//   if (z->left == NULL) {
//     x = z->right;
//     rb_transplant(t, z, z->right);
//   } else if (z->right == NULL) {
//     x = z->left;
//     rb_transplant(t, z, z->left);
//   } else {
//     y = tree_minimum(z->right);
//     y_original_color = y->color;
//     x = y->right;
//     if (y->parent == z) {
//       if (x != NULL) {
//         x->parent = y;
//       }
//     } else {
//       rb_transplant(t, y, y->right);
//       y->right = z->right;
//       y->right->parent = y;
//     }
//     rb_transplant(t, z, y);
//     y->left = z->left;
//     y->left->parent = y;
//     y->color = z->color;
//   }
//   free(z);
//   if (y_original_color == RBTREE_BLACK) {
//     rb_delete_fixup(t, x);
//   }
//   return 0;
// }
//
// static void rb_transplant(rbtree *t, node_t *u, node_t *v) {
//   if (u->parent == NULL) {
//     t->root = v;
//   } else if (u == u->parent->left) {
//     u->parent->left = v;
//   } else {
//     u->parent->right = v;
//   }
//   if (v != NULL) {
//     v->parent = u->parent;
//   }
// }
//
// static void rb_delete_fixup(rbtree *t, node_t *x) {
//   while (x != t->root && (x == NULL || x->color == RBTREE_BLACK)) {
//     if (x == x->parent->left) {
//       node_t *w = x->parent->right;
//       if (w->color == RBTREE_RED) {
//         w->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         left_rotate(t, x->parent);
//         w = x->parent->right;
//       }
//       if ((w->left == NULL || w->left->color == RBTREE_BLACK) &&
//           (w->right == NULL || w->right->color == RBTREE_BLACK)) {
//         w->color = RBTREE_RED;
//         x = x->parent;
//       } else {
//         if (w->right == NULL || w->right->color == RBTREE_BLACK) {
//           w->left->color = RBTREE_BLACK;
//           w->color = RBTREE_RED;
//           right_rotate(t, w);
//           w = x->parent->right;
//         }
//         w->color = x->parent->color;
//         x->parent->color = RBTREE_BLACK;
//         if (w->right != NULL) {
//           w->right->color = RBTREE_BLACK;
//         }
//         left_rotate(t, x->parent);
//         x = t->root;
//       }
//     } else {
//       node_t *w = x->parent->left;
//       if (w->color == RBTREE_RED) {
//         w->color = RBTREE_BLACK;
//         x->parent->color = RBTREE_RED;
//         right_rotate(t, x->parent);
//         w = x->parent->left;
//       }
//       if ((w->right == NULL || w->right->color == RBTREE_BLACK) &&
//           (w->left == NULL || w->left->color == RBTREE_BLACK)) {
//         w->color = RBTREE_RED;
//         x = x->parent;
//       } else {
//         if (w->left == NULL || w->left->color == RBTREE_BLACK) {
//           w->right->color = RBTREE_BLACK;
//           w->color = RBTREE_RED;
//           left_rotate(t, w);
//           w = x->parent->left;
//         }
//         w->color = x->parent->color;
//         x->parent->color = RBTREE_BLACK;
//         if (w->left != NULL) {
//           w->left->color = RBTREE_BLACK;
//         }
//         right_rotate(t, x->parent);
//         x = t->root;
//       }
//     }
//   }
//   if (x != NULL) {
//     x->color = RBTREE_BLACK;
//   }
// }
//
// int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
//   int i = 0;
//   node_t *current = t->root;
//   return inorder_traversal(current, arr, &i, n);
// }
//
// static int inorder_traversal(node_t *x, key_t *arr, int *i, const size_t n) {
//   if (x != NULL && *i < n) {
//     inorder_traversal(x->left, arr, i, n);
//     if (*i < n) {
//       arr[(*i)++] = x->key;
//     }
//     inorder_traversal(x->right, arr, i, n);
//   }
//   return 0;
// }
