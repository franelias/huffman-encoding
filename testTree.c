#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

void test_new_node() {
  TreeNode node1 = new_node('a', 1);
  assert(node1->letter == 'a');
  assert(node1->left == node1->right == NULL);
}

void test_build_letters_array() {
  char *text1 = malloc(sizeof(char) * 10);
  int *len1 = malloc(sizeof(int));
  strcpy(text1, "aabcdefgh");
  TreeNode *treeList1 = build_letters_array(text1, strlen(text1), len1);
  assert(*len1 == 8);
}

void test_fuse_trees() {
  // test 1 caso uno 2 nodos
  TreeNode left1 = new_node('a', 1);
  TreeNode right1 = new_node('b', 1);
  TreeNode result1 = fuse_trees(2, left1, right1, '\0');

  assert(result1->left == left1 && result1->right == right1);
  assert(result1->letter == '\0');

  // test 2 caso con un 1 nodo y el otro vacio
  TreeNode left2 = new_node('a', 1);
  TreeNode right2 = NULL;
  TreeNode result2 = fuse_trees(2, left2, right2, '\0');
  assert(result2->left == left2 && result2->right == right2);
  assert(result2->letter == '\0');

  // test 3 caso con dos nodos vacio
  TreeNode result3 = fuse_trees(3, NULL, NULL, '\0');
  assert(result3->left == result3->right == NULL);
}

void test_destroy_tree() {
  // test 1 destruyo un arbol completo
  TreeNode root1 = new_node('\0', 0);
  TreeNode right1 = new_node('a', 1);
  TreeNode left1 = new_node('b', 1);

  root1->left = left1;
  root1->right = right1;

  destroy_tree(root1);
  assert(root1 == right1 == left1 == NULL);

  // test 2 destruyo un arbol sin hijos
  TreeNode root2 = new_node('\0', 0);
  destroy_tree(root2);
  assert(root2 == NULL);

  // test 3 destruyo un arbol con un hijo izq

  TreeNode root3 = new_node('\0', 0);
  TreeNode left3 = new_node('a', 0);
  root3->left = left3;
  destroy_tree(root3);
  assert(root3 == left3 == NULL);

  // test 4 destruyo un arbol con un hijo der

  TreeNode root4 = new_node('\0', 0);
  TreeNode right4 = new_node('a', 0);
  root4->right = right4;
  destroy_tree(root4);
  assert(root4 == right4 == NULL);

  // test 5 destruyo un arbol vacio (NULL)
  TreeNode root5 = NULL;
  destroy_tree(root5);
  assert(root5 == NULL);
}

int main() {
  test_new_node();
  test_fuse_trees();
  test_destroy_tree();
  return 0;
}