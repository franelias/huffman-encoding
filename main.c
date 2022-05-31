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

char* encoded_file_name(char* fileName) {
  char* outputFileName = malloc(sizeof(char) * strlen(fileName) + 4);
  strcpy(outputFileName, fileName);

  strcat(outputFileName, ".hf");

  return outputFileName;
}

char* tree_file_name(char* fileName) {
  char* treeFileName = malloc(sizeof(char) * strlen(fileName) + 7);
  strcpy(treeFileName, fileName);

  strcat(treeFileName, ".tree");

  return treeFileName;
}

char* decoded_file_name(char* fileName) {
  char* outputFileName = malloc(sizeof(char) * strlen(fileName) + 4);
  strcpy(outputFileName, fileName);

  strcat(outputFileName, ".dec");

  return outputFileName;
}

void free_all(void** pointers, int amount) {
  for (int i = 0; i < amount; i++) {
    free(pointers[i]);
  }
}

void generate_output_files(char* fileName, char* encodedText, char* encodedTree, int length1, int length2) {
  char* outputFileName = encoded_file_name(fileName);
  char* treeFileName = tree_file_name(fileName);

  int* implodedTextLength = malloc(sizeof(int));

  char* implodedText = implode(encodedText, length1, implodedTextLength);

  writefile(outputFileName, implodedText, *implodedTextLength);
  writefile(treeFileName, encodedTree, length2);

  void* pointers[4] = {outputFileName, treeFileName, implodedText, implodedTextLength};

  free_all(pointers, 4);
}

void encoder(char* file) {
  int* contentLength = malloc(sizeof(int));
  int* lettersAmount = malloc(sizeof(int));
  char* encodedLetters[256] = {};

  char* fileContent = readfile(file, contentLength);

  TreeNode* arrayOfTrees = build_letters_array(fileContent, *contentLength, lettersAmount);
  List treeList = array_to_list(arrayOfTrees, *lettersAmount);

  free(arrayOfTrees);

  TreeNode huffmanTree = generate_huffman_tree(treeList, *lettersAmount);
  int* largeBits = malloc(sizeof(int));
  *largeBits = 0;
  find_letters_path(huffmanTree, "", encodedLetters, largeBits);
  char* encodedText = encode_text(fileContent, *contentLength, encodedLetters, *largeBits);

  char* encodedTree = malloc(sizeof(char) * (*lettersAmount) * 2);
  strcpy(encodedTree, "");

  char* lettersInOrder = malloc(sizeof(char) * (*lettersAmount) + 2);

  strcpy(lettersInOrder, "\n");
  int *puntero=malloc(sizeof(int));
  *puntero=1;
  encode_tree(huffmanTree, encodedTree, lettersInOrder,puntero);

  //lettersInOrder[*lettersAmount] = '\0';

  printf("cantidad %ld\n", strlen(lettersInOrder));

  char* encodedTreeWithLetters = malloc(sizeof(char) * strlen(encodedTree) + sizeof(char) * (*lettersAmount) + 1);
  strcpy(encodedTreeWithLetters, encodedTree);
  for(int k=0;k<*puntero;k++){
    encodedTreeWithLetters[strlen(encodedTree)+k]=lettersInOrder[k];
  }
  //strcat(encodedTreeWithLetters, lettersInOrder);

  generate_output_files(file, encodedText, encodedTreeWithLetters, *largeBits, strlen(encodedTree) + (*puntero));

  void* pointers[7] = {fileContent, contentLength, encodedText, encodedTree, lettersInOrder, lettersAmount, encodedTreeWithLetters};

  free_all(pointers, 7);
  free_all((void**)encodedLetters, 256);
  destroy_tree(&huffmanTree);
}

void decoder(char* file) {
  char originalName[BUFFER] = {' '};
  strncpy(originalName, file, strlen(file) - 3);

  char* treeFileName = tree_file_name(originalName);

  int* implodedFileLength = malloc(sizeof(int));
  int* encodedTreeLength = malloc(sizeof(int));

  int* encodedFileLength = malloc(sizeof(int));

  char* implodedFile = readfile(file, implodedFileLength);
  char* encodedTree = readfile(treeFileName, encodedTreeLength);

  char* encodedFile = explode(implodedFile, *implodedFileLength, encodedFileLength);
  char* decodedTree;
  char* leafs;

  // split(encodedTree, &decodedTree, &leafs);
  int *contador1 = malloc(sizeof(int)), *contador2 = malloc(sizeof(int));
  *contador1 = *contador2 = 0;

  TreeNode decodedTreeWL = decode_tree_aux(encodedTree, contador1, contador2);
  int *decodedFileLength=malloc(sizeof(int));
  char* decodedText = decode_text(encodedFile, *encodedFileLength, decodedTreeWL, decodedFileLength);

  writefile(decoded_file_name(originalName), decodedText, *decodedFileLength);
  destroy_tree(&decodedTreeWL);

  // void* pointers[11] = {implodedFileLength, encodedTreeLength, encodedFileLength, implodedFile, encodedFile, decodedTree, contador1, contador2, decodedText, treeFileName};

  // free_all(pointers, 11);
}

int main(int argc, char** argv) {
  encoder("rock.jpeg");
  decoder("rock.jpeg.hf");
  // if (argc < 3) {
  //   exit(1);
  // }

  // if (strcmp(argv[1], ENCODER_ALIAS) == 0) {
  //   encoder(argv[2]);
  // } else if (strcmp(argv[1], DECODER_ALIAS) == 0) {
  //   decoder("prueba.txt.hf");
  // } else {
  //   printf("Invalid arguments");
  // }

  return 0;
}