#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "encode.h"
#include "lists.h"
#include "tree.h"

List create_test_list() {
  List newList = NULL;

  TreeNode node1 = new_node('a', 3);
  TreeNode node2 = new_node('b', 4);
  TreeNode node3 = new_node('c', 5);
  TreeNode node4 = new_node('d', 6);

  push(&newList, node4);
  push(&newList, node3);
  push(&newList, node2);
  push(&newList, node1);

  return newList;
}

void test_decode_text() {
  // decodifico el codigo formado en test_encode_text y verifico que coincida con el texto original
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  int *finalSize = malloc(sizeof(int));
  *finalSize = 0;
  char *decodedText = decode_text("000000010101011010101010111111111111", 36, tree, finalSize);
  assert(*finalSize == 18);
  assert(strcmp(decodedText, "aaabbbbcccccdddddd") == 0);
}

void tets_decode_tree() {
  // decodifico el arbol codificado en test_encode_tree y verifico que coincida con el arbol original
  TreeNode decodedTree = decode_tree_aux("0011011\nabcd");
  assert(decodedTree->left->left->letter == 'a');
  assert(decodedTree->left->right->letter == 'b');
  assert(decodedTree->right->left->letter == 'c');
  assert(decodedTree->right->right->letter == 'd');
}

int main() {
  test_decode_text();
  tets_decode_tree();
  printf("Todos los tests pasaron\n");
  return 0;
}