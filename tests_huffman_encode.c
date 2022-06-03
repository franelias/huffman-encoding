#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encode.h"
#include "lists.h"
#include "tree.h"

List create_test_list()
{
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

void test_generate_huffman_tree()
{
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
}

void test_find_letters_path()
{
  // creo un arbol de huffman y lo recorro para ver que se guarden correctamente los paths
  // y el tamaño final que tendra el contenido del archivo codificado
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  char *paths[256];
  int *size = malloc(sizeof(int));
  *size = 0;
  find_letters_path(tree, "", paths, size);
  assert(strcmp(paths['a'], "00") == 0);
  assert(strcmp(paths['b'], "01") == 0);
  assert(strcmp(paths['c'], "10") == 0);
  assert(strcmp(paths['d'], "11") == 0);
  assert(*size == 36);
}

void test_encode_text()
{
  // codifico un texto y verifico que este correctamente codificado
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  char *paths[256];
  int *size = malloc(sizeof(int));
  *size = 0;
  find_letters_path(tree, "", paths, size);
  char *encodedText = encode_text("aaabbbbcccccdddddd", 18, *size, paths);
  assert(strcmp(encodedText, "000000010101011010101010111111111111") == 0);
}

void test_encode_tree()
{
  // codifico el arbol y veo que este correctamente codificado
  // y que sus hojas esten en el orden correcto, y que el tamaño final este correcto
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  int *size = malloc(sizeof(int));
  *size = 0;
  char *encodedTree = encode_tree(tree, 4, size);

  assert(strcmp(encodedTree, "0011011\nabcd") == 0);

  assert(*size == 12);
}
int main()
{
  test_generate_huffman_tree();
  test_find_letters_path();
  test_encode_text();
  test_encode_tree();

  printf("Todos los tests pasaron\n");
  return 0;
}