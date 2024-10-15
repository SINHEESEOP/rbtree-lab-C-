#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

// 테스트가 아닌 일단 구현한 내용 임시로 실행해보는 용도
// 추가로 실제로 나중에 테스트가 통과되면 rbtree 를 이용하여 드라이버로 만들 파일.
int main(int argc, char *argv[]) {
  // 레드-블랙 트리 생성
  rbtree *t = new_rbtree();
  if (t == NULL) {
    fprintf(stderr, "레드-블랙 트리 생성에 실패했습니다.\n");
    return 1;
  }

  // 키 값 배열
  key_t keys[] = {20, 15, 25, 10, 18, 22, 30, 6, 12, 17, 19};
  size_t n = sizeof(keys) / sizeof(keys[0]);

  // 트리에 키 삽입
  for (size_t i = 0; i < n; i++) {
    node_t *node = rbtree_insert(t, keys[i]);
    if (node == NULL) {
      fprintf(stderr, "레드-블랙 트리에 키 %d 삽입에 실패했습니다.\n", keys[i]);
      delete_rbtree(t);
      return 1;
    }
  }

  // 트리를 중위 순회하여 정렬된 키 출력
  key_t *arr = calloc(n, sizeof(key_t));
  if (arr == NULL) {
    fprintf(stderr, "배열에 대한 메모리 할당에 실패했습니다.\n");
    delete_rbtree(t);
    return 1;
  }
  rbtree_to_array(t, arr, n);
  printf("레드-블랙 트리의 중위 순회 결과:\n");
  for (size_t i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  // 특정 키 검색
  key_t search_key = 18;
  node_t *found_node = rbtree_find(t, search_key);
  if (found_node != NULL) {
    printf("키 %d가 레드-블랙 트리에서 발견되었습니다.\n", search_key);
  } else {
    printf("키 %d가 레드-블랙 트리에서 발견되지 않았습니다.\n", search_key);
  }

  // 최소값과 최대값 출력
  node_t *min_node = rbtree_min(t);
  node_t *max_node = rbtree_max(t);
  if (min_node != NULL && max_node != NULL) {
    printf("트리의 최소 키: %d\n", min_node->key);
    printf("트리의 최대 키: %d\n", max_node->key);
  }

  // 키 삭제
  key_t delete_key = 15;
  node_t *delete_node = rbtree_find(t, delete_key);
  if (delete_node != NULL) {
    rbtree_erase(t, delete_node);
    printf("키 %d가 레드-블랙 트리에서 삭제되었습니다.\n", delete_key);
  } else {
    printf("키 %d가 레드-블랙 트리에서 발견되지 않았습니다.\n", delete_key);
  }

  // 삭제 후 트리 중위 순회 결과 출력
  rbtree_to_array(t, arr, n);
  printf("삭제 후 중위 순회 결과:\n");
  for (size_t i = 0; i < n; i++) {
    if (arr[i] != delete_key) {  // 삭제된 키는 출력하지 않음
      printf("%d ", arr[i]);
    }
  }
  printf("\n");

  // 메모리 해제
  free(arr);
  delete_rbtree(t);

  return 0;
}