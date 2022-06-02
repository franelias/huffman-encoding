#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lists.h"
#include "tree.h"
#include "huffman.h"

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
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  char *paths[256];
  int *size = malloc(sizeof(int));
  *size = 0;
  find_letters_path(tree, "", paths, size);
  char *encodedText = encode_text("aaabbbbcccccdddddd", 18, paths, *size);
  assert(strcmp(encodedText, "000000010101011010101010111111111111") == 0);
  assert(*size == 36);
}

void test_encode_tree()
{
  List list = create_test_list();
  TreeNode tree = generate_huffman_tree(list, 4);
  int *size = malloc(sizeof(int));
  *size = 0;
  char *encodedTree = malloc(sizeof(char) * 8);
  strcpy(encodedTree, "");
  char *letters = malloc(sizeof(char) * 4);
  strcpy(letters, "");
  encode_tree(tree, encodedTree, letters, size);

  assert(strcmp(encodedTree, "0011011") == 0);
  assert(strcmp(letters, "abcd") == 0);
  assert(*size == 4);
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