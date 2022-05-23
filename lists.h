#ifndef __LISTS_H_
#define __LISTS_H_

#include "tree.h"

typedef struct _nodeList {
  TreeNode tree;
  struct _nodeList* next;
} nodeList;

typedef nodeList* List;

void sorted_insert(List* head, List node);

void push(List* list, TreeNode data);

List array_to_list(TreeNode *array, int length);

void destroy_list(List list);

void remove_first(List* list);

#endif
