#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "io.h"
#include "lists.h"
#include "tree.h"

#define BUFFER 32

int main() {
  int* length = malloc(sizeof(int));
  int* amount = malloc(sizeof(int));

  char* text = readfile("prueba.txt", length);
  char* encodeLetters[256];

  for (int i = 0; i < 256; i++) {
    encodeLetters[i] = NULL;
  }

  TreeNode* array = read_text(text, *length, amount);
  List listOfTrees = array_to_list(array, *amount);

  TreeNode huffmanTree = generate_huffman_tree(listOfTrees, *amount);

  tree_in_order(huffmanTree, "", encodeLetters);
  char* encodedText = encode_text(text, *length, encodeLetters);

  printf("%s %ld\n", encodedText, strlen(encodedText));

  writefile("huff.hf", encodedText, strlen(encodedText));

  // char* encodedTree = malloc(sizeof(char));
  // strcpy(encodedTree, "");
  // encode_tree(huffmanTree, encodedTree);
  // writefile("huff.tree", encodedTree, strlen(encodedTree));

  char* caca = decode_text(encodedText, huffmanTree);

  printf("%s\n", caca);

  free(text);
  free(array);
  free(length);
  free(amount);
  free(encodedText);
  for (int i = 0; i < 256; i++)
    free(encodeLetters[i]);
  destroyTree(huffmanTree);
  free(caca);

  return 0;
}
