#include "rbtree.h"
#include <stdlib.h>

static void rbtree_delete_node(rbtree *t, node_t *node);
static void left_rotate(rbtree *t, node_t *x);
static void right_rotate(rbtree *t, node_t *x);
static void rbtree_insert_fixup(rbtree *t, node_t *z);
static node_t *tree_minimum(rbtree *t, node_t *x);
static node_t *tree_maximum(rbtree *t, node_t *x);
static void rb_transplant(rbtree *t, node_t *u, node_t *v);
static void rb_delete_fixup(rbtree *t, node_t *x);
static int inorder_traversal(const rbtree *t, node_t *x, key_t *arr, int i, const size_t n);

rbtree *new_rbtree(void) {
  rbtree *t = (rbtree *)calloc(1, sizeof(rbtree));
  if (t == NULL) {
    return NULL;
  }

  // nil 노드 할당
  node_t *nil_node = (node_t *)calloc(1, sizeof(node_t));
  if (nil_node == NULL) { // 이때 nil 은 실패하여, 따로 해제 할 필요가 없고 위에 tree 만 해제 하면 된다.
    free(t);
    return NULL;
  }

  nil_node->color = RBTREE_BLACK; // nil은 검정색
  nil_node->left = nil_node->right = nil_node->parent = nil_node;

  t->nil = nil_node;
  t->root = t->nil;

  return t;
}

void delete_rbtree(rbtree *t) {
  if (t != NULL) {
    rbtree_delete_node(t, t->root);
    free(t->nil);
    free(t);
  }
}

static void rbtree_delete_node(rbtree *t, node_t *node) {
  if (node != t->nil) {
    rbtree_delete_node(t, node->left);
    rbtree_delete_node(t, node->right);
    free(node);
  }
}

static void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right; // y 설정
  x->right = y->left;   // y의 왼쪽 서브트리를 x의 오른쪽 서브트리로 변환
  if (y->left != t->nil) {
    y->left->parent = x;
  }
  y->parent = x->parent; // x의 부모를 y로 연결
  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;  // x를 y의 왼쪽에 놓음
  x->parent = y;
}

static void right_rotate(rbtree *t, node_t *x) {
  node_t *y = x->left;  // y 설정
  x->left = y->right;   // y의 오른쪽 서브트리를 x의 왼쪽 서브트리로 변환
  if (y->right != t->nil) {
    y->right->parent = x;
  }
  y->parent = x->parent; // x의 부모를 y로 연결
  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;  // x를 y의 오른쪽에 놓음
  x->parent = y;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  node_t *z = (node_t *)malloc(sizeof(node_t));
  if (z == NULL) {
    return NULL;
  }
  z->key = key;
  z->left = z->right = z->parent = t->nil;

  node_t *y = t->nil;
  node_t *x = t->root;

  while (x != t->nil) {
    y = x;
    if (key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  z->parent = y;
  if (y == t->nil) {
    t->root = z;
  } else if (key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
  z->left = z->right = t->nil;
  z->color = RBTREE_RED;

  rbtree_insert_fixup(t, z);

  return z;
}

static void rbtree_insert_fixup(rbtree *t, node_t *z) {
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left) {
      node_t *y = z->parent->parent->right;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;        // 케이스 1
        y->color = RBTREE_BLACK;                // 케이스 1
        z->parent->parent->color = RBTREE_RED;  // 케이스 1
        z = z->parent->parent;                  // 케이스 1
      } else {
        if (z == z->parent->right) {
          z = z->parent;                        // 케이스 2
          left_rotate(t, z);                    // 케이스 2
        }
        z->parent->color = RBTREE_BLACK;        // 케이스 3
        z->parent->parent->color = RBTREE_RED;  // 케이스 3
        right_rotate(t, z->parent->parent);     // 케이스 3
      }
    } else {
      node_t *y = z->parent->parent->left;
      if (y->color == RBTREE_RED) {
        z->parent->color = RBTREE_BLACK;        // 케이스 1
        y->color = RBTREE_BLACK;                // 케이스 1
        z->parent->parent->color = RBTREE_RED;  // 케이스 1
        z = z->parent->parent;                  // 케이스 1
      } else {
        if (z == z->parent->left) {
          z = z->parent;                        // 케이스 2
          right_rotate(t, z);                   // 케이스 2
        }
        z->parent->color = RBTREE_BLACK;        // 케이스 3
        z->parent->parent->color = RBTREE_RED;  // 케이스 3
        left_rotate(t, z->parent->parent);      // 케이스 3
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  node_t *x = t->root;
  while (x != t->nil) {
    if (key == x->key) {
      return x;
    } else if (key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  if (t->root == t->nil) {
    return NULL;
  }
  return tree_minimum((rbtree *)t, t->root);
}

static node_t *tree_minimum(rbtree *t, node_t *x) {
  while (x->left != t->nil) {
    x = x->left;
  }
  return x;
}

node_t *rbtree_max(const rbtree *t) {
  if (t->root == t->nil) {
    return NULL;
  }
  return tree_maximum((rbtree *)t, t->root);
}

static node_t *tree_maximum(rbtree *t, node_t *x) {
  while (x->right != t->nil) {
    x = x->right;
  }
  return x;
}

int rbtree_erase(rbtree *t, node_t *z) {
  node_t *y = z;
  node_t *x;
  color_t y_original_color = y->color;

  if (z->left == t->nil) {
    x = z->right;
    rb_transplant(t, z, z->right);
  } else if (z->right == t->nil) {
    x = z->left;
    rb_transplant(t, z, z->left);
  } else {
    y = tree_minimum(t, z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  free(z);
  if (y_original_color == RBTREE_BLACK) {
    rb_delete_fixup(t, x);
  }
  return 0;
}

static void rb_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) {
    t->root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

static void rb_delete_fixup(rbtree *t, node_t *x) {
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left) {
      node_t *w = x->parent->right;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;          // 케이스 1
        x->parent->color = RBTREE_RED;    // 케이스 1
        left_rotate(t, x->parent);        // 케이스 1
        w = x->parent->right;             // w 업데이트
      }
      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;            // 케이스 2
        x = x->parent;                    // 트리 상단으로 이동
      } else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;  // 케이스 3
          w->color = RBTREE_RED;          // 케이스 3
          right_rotate(t, w);             // 케이스 3
          w = x->parent->right;           // w 업데이트
        }
        w->color = x->parent->color;      // 케이스 4
        x->parent->color = RBTREE_BLACK;  // 케이스 4
        w->right->color = RBTREE_BLACK;   // 케이스 4
        left_rotate(t, x->parent);        // 케이스 4
        x = t->root;                      // 루프 종료
      }
    } else {
      node_t *w = x->parent->left;
      if (w->color == RBTREE_RED) {
        w->color = RBTREE_BLACK;          // 케이스 1
        x->parent->color = RBTREE_RED;    // 케이스 1
        right_rotate(t, x->parent);       // 케이스 1
        w = x->parent->left;              // w 업데이트
      }
      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;            // 케이스 2
        x = x->parent;                    // 트리 상단으로 이동
      } else {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK; // 케이스 3
          w->color = RBTREE_RED;          // 케이스 3
          left_rotate(t, w);              // 케이스 3
          w = x->parent->left;            // w 업데이트
        }
        w->color = x->parent->color;      // 케이스 4
        x->parent->color = RBTREE_BLACK;  // 케이스 4
        w->left->color = RBTREE_BLACK;    // 케이스 4
        right_rotate(t, x->parent);       // 케이스 4
        x = t->root;                      // 루프 종료
      }
    }
  }
  x->color = RBTREE_BLACK;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  inorder_traversal(t, t->root, arr, 0, n);
  return 0;
}

static int inorder_traversal(const rbtree *t, node_t *x, key_t *arr, int i, const size_t n) {
  if (x != t->nil && i < n) {
    i = inorder_traversal(t, x->left, arr, i, n);
    if (i < n) {
      arr[i++] = x->key;
    }
    i = inorder_traversal(t, x->right, arr, i, n);
  }
  return i;
}
