#include <stdio.h>
#include <stdlib.h>

#include "lists.h"
#include "tree.h"

List create_test_list() {
  List newList = create_list();

  TreeNode node1 = new_node('a', 3);
  TreeNode node2 = new_node('b', 4);
  TreeNode node3 = new_node('c', 5);
  TreeNode node4 = new_node('d', 6);

  push(newList, node1);
  push(newList, node2);
  push(newList, node3);
  push(newList, node4);

  return newList;
}

void test_generate_huffman_tree() {
}

int main() {
  return 0;
}