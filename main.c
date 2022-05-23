#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "io.h"
#include "lists.h"
#include "tree.h"

#define BUFFER 32

char* output_file_name(char* fileName) {
  char* outputFileName = malloc(sizeof(char) * strlen(fileName) + 4);
  strcpy(outputFileName, fileName);

  strcat(outputFileName, ".hf");

  return outputFileName;
}

char* tree_file_name(char* fileName) {
  printf("%ld\n",strlen(fileName));
  char* treeFileName = malloc(sizeof(char) * strlen(fileName) + 7);
  strcpy(treeFileName, fileName);

  strcat(treeFileName, ".tree");

  return treeFileName;
}

void generate_output_files(char* fileName, char* encodedText, char* encodedTree) {
  char* outputFileName = output_file_name(fileName);
  char* treeFileName = tree_file_name(fileName);

  int* implodedTextLength = malloc(sizeof(int));

  char* implodedText = implode(encodedText, strlen(encodedText), implodedTextLength);

  writefile(outputFileName, implodedText, *implodedTextLength);
  writefile(treeFileName, encodedTree, strlen(encodedTree));

  free(outputFileName);
  free(treeFileName);
  free(implodedText);
  free(implodedTextLength);
}

int main() {
  int* contentLength = malloc(sizeof(int));
  int* lettersAmount = malloc(sizeof(int));
  char* encodedLetters[256] = {NULL};
  // encodedLetters['a'] = "0101010"

  char fileName[BUFFER];

  printf("Ingrese el nombre del archivo: ");
  scanf("%s", fileName);

  char* fileContent = readfile(fileName, contentLength); // 9 allocs

  TreeNode* arrayOfTrees = build_letters_array(fileContent, *contentLength, lettersAmount); //41 allocs
  List treeList = array_to_list(arrayOfTrees, *lettersAmount); // 40 allocs

  free(arrayOfTrees);

  TreeNode huffmanTree = generate_huffman_tree(treeList, *lettersAmount); // 78 allocs
  
  find_letters_path(huffmanTree, "", encodedLetters);

  char* encodedText = encode_text(fileContent, *contentLength, encodedLetters);

  char* encodedTree = malloc(sizeof(char) * *lettersAmount * 2 );
  strcpy(encodedTree, "");

  char* lettersInOrder = malloc(sizeof(char) * (*lettersAmount) + 2);

  strcpy(lettersInOrder, "\n");
  encode_tree(huffmanTree, encodedTree, lettersInOrder);

  char* encodedTreeWithLetters = malloc(sizeof(char) * strlen(encodedTree) + sizeof(char) * strlen(lettersInOrder) + 1);
  strcpy(encodedTreeWithLetters, encodedTree);
  strcat(encodedTreeWithLetters, lettersInOrder);

  generate_output_files(fileName, encodedText, encodedTreeWithLetters);

  for (int i = 0; i < 256; i++)
    free(encodedLetters[i]);
  free(fileContent);
  free(contentLength);
  free(encodedText);
  free(encodedTree);
  free(lettersInOrder);
  free(lettersAmount);
  free(encodedTreeWithLetters);
  destroy_tree(huffmanTree);
  
  return 0;
}
