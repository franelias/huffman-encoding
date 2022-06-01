#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode generate_huffman_tree(List letters, int length) {
  TreeNode newTree, huffmanTree;
  List firstNode, secondNode;
  int weight;

  while (length > 1) {
    firstNode = letters;
    secondNode = letters->next;

    weight = firstNode->tree->weight + secondNode->tree->weight;

    newTree = fuse_trees(weight, firstNode->tree, secondNode->tree, '\0');

    letters = letters->next->next;

    List newNode = malloc(sizeof(nodeList));
    newNode->next = NULL;
    newNode->tree = newTree;

    free(firstNode);
    free(secondNode);

    sorted_insert(&letters, newNode);
    length--;
  }

  huffmanTree = letters->tree;

  free(letters);

  return huffmanTree;
}

void find_letters_path(TreeNode tree, char arr[], int top, char *results[], int *largeBits) {
  if (tree->left) {
    arr[top] = '0';
    find_letters_path(tree->left, arr, top + 1, results, largeBits);
  }

  if (tree->right) {
    arr[top] = '1';
    find_letters_path(tree->right, arr, top + 1, results, largeBits);
  }

  if (tree->left == NULL && tree->right == NULL) {
    arr[top] = '\0';
    int largePath = strlen(arr) + 1;
    char *path = malloc(sizeof(char) * largePath);
    *largeBits = *largeBits + largePath * tree->weight;
    strcpy(path, arr);

    results[(unsigned char)tree->letter] = path;
    // printf("%s %c \n", path, tree->letter);
  }
}

char *encode_text(char *text, int length, char *encodedLetters[], int size) {
  char *encodedText = malloc(sizeof(char) * size + 1);

  strcpy(encodedText, "");
  int tempSize = 0;

  int encodedLettersLength[256] = {0};
  // printf("%d \n", length);
  for (int i = 0; i < length; i++) {
    // printf("%c %d %d %d %d %s\n", text[i], (unsigned char)text[i],  tempSize, size, length, encodedLetters[(unsigned char)text[i]]);
    strcpy(encodedText + tempSize, encodedLetters[(unsigned char)text[i]]);
    // printf("%s \n", encodedText);
    if (encodedLettersLength[(unsigned char)text[i]] == 0) {
      encodedLettersLength[(unsigned char)text[i]] = strlen(encodedLetters[(unsigned char)text[i]]);
    }
    /// bugardo aca
    tempSize += encodedLettersLength[(unsigned char)text[i]];
    ///  posible solucion pero sigue fallando no se porque
    // tempSize += encodedLettersLength[(unsigned char)text[i]] + 1;
  }
  // printf("%d   %s     %d      %ld\n", tempSize, encodedText, size, strlen(encodedText));
  return encodedText;
}

char *decode_text(char *encodedText, int encodedFileLength, TreeNode tree) {
  TreeNode root = tree;

  char *decodedText = malloc(sizeof(char) + 2);
  strcpy(decodedText, "");

  int size = 2;
  int tempSize = 0;
  for (int i = 0; i < encodedFileLength; i++) {
    // printf("%c ----", encodedText[i]);
    if (encodedText[i] == '0') {
      tree = tree->left;
    } else {
      tree = tree->right;
    }

    if (tree->left == NULL && tree->right == NULL) {
      if (size <= tempSize + 1) {
        size = (int)((tempSize + 2) * 1.5);
        decodedText = realloc(decodedText, sizeof(char) * size);
      }
      decodedText[tempSize] = tree->letter;
      // printf("%c %c\n", tree->letter, decodedText[tempSize]);
      tempSize++;
      tree = root;
    }
  }
  // printf("\n -------------------\n%c\n", decodedText[100]);
  decodedText[tempSize] = '\0';

  return decodedText;
}

// sacar
int kk = 1;

void encode_tree(TreeNode tree, char *encodedTree, char *letters) {
  if (tree == NULL) {
    return;
  }

  char *aux = malloc(sizeof(char) * 2);

  if (tree->left == NULL && tree->right == NULL) {
    strcat(encodedTree, "1");

    letters[kk] = tree->letter;
    kk++;
  } else {
    strcat(encodedTree, "0");
  }

  encode_tree(tree->left, encodedTree, letters);
  encode_tree(tree->right, encodedTree, letters);
  free(aux);
}
int cont1 = 0, cont2 = 0;
TreeNode decode_tree(char *encodedTree, int encodedTreeLength, int *encodedTreePos, char *leafs, int leafsLength, int *leafsPos) {
  // for (int i = 0; i < leafsLength; i++) {
  //   printf("%d ", (unsigned char)leafs[i]);
  // }

  TreeNode newNode = new_node('\0', 0);

  if (encodedTreeLength == cont1 || leafsLength == cont2) {
    return newNode;
  }

  if (encodedTree[cont1] == '0') {
    *encodedTreePos = *encodedTreePos + 1;
    cont1++;
    newNode->left = decode_tree(encodedTree, encodedTreeLength, encodedTreePos, leafs, leafsLength, leafsPos);
    newNode->right = decode_tree(encodedTree, encodedTreeLength, encodedTreePos, leafs, leafsLength, leafsPos);
  } else {
    *encodedTreePos = (*encodedTreePos) + 1;
    cont1++;
    newNode->letter = (unsigned char)leafs[cont2];
    cont2++;
    *leafsPos = (*leafsPos) + 1;
  }
  return newNode;
}

void split(char *encodedTree, int encodedTreeLength, char **decodedTree, char **leafs) {
  int h = 0;
  for (int i = 0; encodedTree[i] != '\n'; i++) {
    (*decodedTree)[i] = (unsigned char)encodedTree[i];
  }
  printf("%c", encodedTree[strlen(*decodedTree) + 1]);
  (*decodedTree)[strlen(*decodedTree)] = '\0';
  for (int j = strlen((*decodedTree)) + 1; j < encodedTreeLength; j++) {
    (*leafs)[h++] = (unsigned char)encodedTree[j];
  }
  (*leafs)[strlen(*leafs)] = '\0';
  printf("%s\n", *leafs);
}
