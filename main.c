#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "huffman.h"
#include "io.h"
#include "lists.h"
#include "tree.h"

#define ENCODER_ALIAS "C"
#define DECODER_ALIAS "D"
#define BUFFER 32

char *encoded_file_name(char *fileName) {
  char *outputFileName = malloc(sizeof(char) * strlen(fileName) + 4);
  strcpy(outputFileName, fileName);

  strcat(outputFileName, ".hf");

  return outputFileName;
}

char *tree_file_name(char *fileName) {
  char *treeFileName = malloc(sizeof(char) * strlen(fileName) + 7);
  strcpy(treeFileName, fileName);

  strcat(treeFileName, ".tree");

  return treeFileName;
}

char *decoded_file_name(char *fileName) {
  char *outputFileName = malloc(sizeof(char) * strlen(fileName) + 4);
  strcpy(outputFileName, fileName);

  strcat(outputFileName, ".dec");

  return outputFileName;
}

void free_all(void **pointers, int amount) {
  for (int i = 0; i < amount; i++) {
    free(pointers[i]);
  }
}

void generate_output_files(char *fileName, char *encodedText, char *encodedTree, int encodedTreeLength) {
  char *outputFileName = encoded_file_name(fileName);
  char *treeFileName = tree_file_name(fileName);

  int *implodedTextLength = malloc(sizeof(int));

  char *implodedText = implode(encodedText, strlen(encodedText), implodedTextLength);

  writefile(outputFileName, implodedText, *implodedTextLength);
  writefile(treeFileName, encodedTree, encodedTreeLength);

  void *pointers[4] = {outputFileName, treeFileName, implodedText, implodedTextLength};

  free_all(pointers, 4);
}

void encoder(char *file) {
  int *contentLength = malloc(sizeof(int));
  int *lettersAmount = malloc(sizeof(int));
  char *encodedLetters[256] = {NULL};

  char *fileContent = readfile(file, contentLength);

  TreeNode *arrayOfTrees = build_letters_array(fileContent, *contentLength, lettersAmount);
  List treeList = array_to_list(arrayOfTrees, *lettersAmount);

  free(arrayOfTrees);

  TreeNode huffmanTree = generate_huffman_tree(treeList, *lettersAmount);
  int *largeBits = malloc(sizeof(int));
  *largeBits = 0;
  // print_arbol(huffmanTree);

  // funcion que devuelva el camino mas largo
  // pensar un poco mejor la cota de arr
  char arr[(*lettersAmount)], top = 0;

  find_letters_path(huffmanTree, arr, top, encodedLetters, largeBits);

  // printCodes(huffmanTree, arr, top);

  // find_letters_path(huffmanTree, "", encodedLetters, largeBits);

  char *encodedText = encode_text(fileContent, *contentLength, encodedLetters, *largeBits);

  char *encodedTree = malloc(sizeof(char) * (*lettersAmount) * 2);
  strcpy(encodedTree, "");

  char *lettersInOrder = malloc(sizeof(char) * (*lettersAmount) + 2);

  strcpy(lettersInOrder, "\n");

  encode_tree(huffmanTree, encodedTree, lettersInOrder);

  char *encodedTreeWithLetters = malloc(sizeof(char) * (*lettersAmount) * 3 + 4);
  strcpy(encodedTreeWithLetters, encodedTree);
  strcat(encodedTreeWithLetters, lettersInOrder);

  int a = (*lettersAmount) * 3 + 4;
  // printf("%s", encodedText);

  generate_output_files(file, encodedText, encodedTreeWithLetters, a);

  void *pointers[7] = {fileContent, contentLength, encodedText, encodedTree, lettersInOrder, lettersAmount, encodedTreeWithLetters};

  free_all(pointers, 7);
  free_all((void **)encodedLetters, 256);
  destroy_tree(&huffmanTree);
}

void decoder(char *file) {
  char originalName[BUFFER] = {' '};
  strncpy(originalName, file, strlen(file) - 3);

  char *treeFileName = tree_file_name(originalName);

  int *implodedFileLength = malloc(sizeof(int));
  int *encodedTreeLength = malloc(sizeof(int));

  int *encodedFileLength = malloc(sizeof(int));

  char *implodedFile = readfile(file, implodedFileLength);
  char *encodedTree = readfile(treeFileName, encodedTreeLength);

  char *encodedFile = explode(implodedFile, *implodedFileLength, encodedFileLength);
  int decodedTreeLength = (int)((*encodedTreeLength) - 2) * 2 / 3, leafLength = (int)((*encodedTreeLength) - 2) / 3;
  char *treePath = malloc(sizeof(char) * decodedTreeLength);
  char *leafs = malloc(sizeof(char) * leafLength);

  split(encodedTree, (*encodedTreeLength), &treePath, &leafs);

  int *contador1 = malloc(sizeof(int)), *contador2 = malloc(sizeof(int));
  *contador1 = 0;
  *contador2 = 0;

  test(treePath, leafs, leafLength);

  TreeNode decodedTreeWL = decode_tree(treePath, strlen(treePath), contador1, leafs, leafLength, contador2);
  // printf("\n");
  // print_arbol(decodedTreeWL);
  char *decodedText = decode_text(encodedFile, *encodedFileLength, decodedTreeWL);

  writefile(decoded_file_name(originalName), decodedText, strlen(decodedText));

  destroy_tree(&decodedTreeWL);

  void *pointers[11] = {implodedFileLength, encodedTreeLength, encodedFileLength, implodedFile, encodedFile, treePath, contador1, contador2, decodedText, treeFileName};

  free_all(pointers, 11);
}

int main(int argc, char **argv) {
  // encoder("grr.jpeg");
  decoder("grr.jpeg.hf");
  //   if (argc < 3) {
  //     exit(1);
  //   }

  // if (strcmp(argv[1], ENCODER_ALIAS) == 0) {
  //   encoder(argv[2]);
  // } else if (strcmp(argv[1], DECODER_ALIAS) == 0) {
  //   decoder("prueba.txt.hf");
  // } else {
  //   printf("Invalid arguments");
  // }

  return 0;
}
