#include "lists.h"

#include <stdio.h>
#include <stdlib.h>

List create_list() {
  return NULL;
}

void sorted_insert(List* head, List node) {
  if (*head == NULL || (*head)->tree->weight >= node->tree->weight) {
    node->next = *head;
    *head = node;
  } else {
    List current = *head;
    while (current->next != NULL && current->next->tree->weight < node->tree->weight) {
      current = current->next;
    }

    node->next = current->next;
    current->next = node;
  }
}

void push(List* list, TreeNode data) {
  List newNode = malloc(sizeof(nodeList));
  newNode->tree = data;
  newNode->next = *list;
  *list = newNode;
}

List array_to_list(TreeNode* array, int length) {
  List list = create_list();

  for (int i = length - 1; i >= 0; i--) {
    push(&list, array[i]);
  }

  return list;
}

void destroy_list(List* list) {
  if (*list) {
    List next = (*list)->next;
    destroy_list(&next);

    TreeNode tree = (*list)->tree;
    if (tree)
      destroy_tree(&tree);

    free(*list);
    *list = NULL;
  }
}

void remove_first(List* list) {
  List tmp;
  if (list == NULL || *list == NULL) return;

  tmp = *list;
  *list = (*list)->next;

  free(tmp);
}