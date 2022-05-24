#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "io.h"
#include "lists.h"
#include "tree.h"

#define BUFFER 32

int main() {
  char fileName[BUFFER];
  char treeFileName[BUFFER];

  int* implodedFileLength = malloc(sizeof(int));
  int* encodedTreeLength = malloc(sizeof(int));

  int* encodedFileLength = malloc(sizeof(int));

  printf("Archivo: ");
  scanf("%s", fileName);

  printf("Árbol: ");
  scanf("%s", treeFileName);

  char* implodedFile = readfile(fileName, implodedFileLength);
  char* encodedTree = readfile(treeFileName, encodedTreeLength);

  char* encodedFile = explode(implodedFile, *implodedFileLength, encodedFileLength);
  char* decodedTree;
  char* leafs;

  split(encodedTree, &decodedTree, &leafs);
  int *contador1 = malloc(sizeof(int)), *contador2 = malloc(sizeof(int));
  *contador1 = *contador2 = 0;

  TreeNode decodedTreeWL = decode_tree(decodedTree, contador1, leafs, contador2);
  char* decodedText = decode_text(encodedFile, *encodedFileLength, decodedTreeWL);
  printf("%s\n", decodedText);

  destroy_tree(decodedTreeWL);
  free(implodedFileLength);
  free(encodedTreeLength);
  free(encodedFileLength);
  free(implodedFile);
  free(encodedFile);
  free(decodedTree);
  free(contador1);
  free(contador2);
  free(decodedText);
  return 0;
}