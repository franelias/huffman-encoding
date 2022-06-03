#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* original_name(char* fileName) {
  char* originalName = malloc(sizeof(char) * strlen(fileName) - 3);

  strncpy(originalName, fileName, strlen(fileName) - 3);

  return originalName;
}

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