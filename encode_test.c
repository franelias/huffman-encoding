#include "encode.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
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

void test_generate_huffman_tree() {
  List list = create_test_list();
  TreeNode huffmanTree = generate_huffman_tree(list, 4);
  //          18
  //    7          11
  //  a   b        c   d
  assert(huffmanTree->weight == 18);
  assert(huffmanTree->right->weight == 11);
  assert(huffmanTree->left->weight == 7);
  assert(huffmanTree->left->left->letter == 'a');
  assert(huffmanTree->left->right->letter == 'b');
  assert(huffmanTree->right->left->letter == 'c');
  assert(huffmanTree->right->right->letter == 'd');
  destroy_tree(&huffmanTree);
}

void test_find_letters_path() {
  // creo un arbol de huffman y lo recorro para ver que se guarden correctamente los paths
  // y el tamaño final que tendra el contenido del archivo codificado
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  char *paths[256] = {};
  int *size = malloc(sizeof(int));
  *size = 0;
  find_letters_path(tree, "", paths, size);
  assert(strcmp(paths['a'], "00") == 0);
  assert(strcmp(paths['b'], "01") == 0);
  assert(strcmp(paths['c'], "10") == 0);
  assert(strcmp(paths['d'], "11") == 0);
  assert(*size == 36);
  destroy_tree(&tree);
  free(size);
  free_all((void **)paths, 256);
}

void test_encode_text() {
  // codifico un texto y verifico que este correctamente codificado
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  char *paths[256] = {};
  int *size = malloc(sizeof(int));
  *size = 0;
  find_letters_path(tree, "", paths, size);
  char *encodedText = encode_text("aaabbbbcccccdddddd", 18, *size, paths);
  assert(strcmp(encodedText, "000000010101011010101010111111111111") == 0);

  destroy_tree(&tree);
  free(size);
  free(encodedText);
  free_all((void **)paths, 256);
}

void test_serialize_tree() {
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  char *encodedTree = malloc(sizeof(char) * 8);
  strcpy(encodedTree, "");
  char *letters = malloc(sizeof(char) * 4);
  strcpy(letters, "");
  int *lettersCount = malloc(sizeof(int));
  *lettersCount = 0;

  serialize_tree(tree, encodedTree, letters, lettersCount);
  letters[*lettersCount] = '\0';
  assert(strcmp(encodedTree, "0011011") == 0);
  assert(strcmp(letters, "abcd") == 0);
  assert(*lettersCount == 4);
  destroy_tree(&tree);
  free(encodedTree);
  free(letters);
  free(lettersCount);
}

void test_encode_tree() {
  // codifico el arbol y veo que este correctamente codificado
  // y que sus hojas esten en el orden correcto, y que el tamaño final este correcto
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  int *size = malloc(sizeof(int));
  *size = 0;
  char *encodedTree = encode_tree(tree, 4, size);

  assert(strcmp(encodedTree, "0011011\nabcd") == 0);
  assert(*size == 13);
  free(size);
  free(encodedTree);
  destroy_tree(&tree);
}

int main() {
  test_generate_huffman_tree();
  test_find_letters_path();
  test_encode_text();
  test_serialize_tree();
  test_encode_tree();

  printf("Todos los tests pasaron\n");
  return 0;
}