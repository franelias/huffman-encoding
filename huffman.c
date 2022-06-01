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

void find_letters_path(TreeNode tree, char arr[], int top, char* results[]) {
  if (tree->left) {
    arr[top] = '0';
    find_letters_path(tree->left, arr, top + 1, results);
  }

  if (tree->right) {
    arr[top] = '1';
    find_letters_path(tree->right, arr, top + 1, results);
  }

  if (tree->left == NULL && tree->right == NULL) {
    arr[top+1] = '\0';
    char* path = malloc(sizeof(char) * strlen(arr) + 1);

    strcpy(path, arr);
    results[(unsigned char)tree->letter] = path;
  }
}

char* encode_text(char* text, int length, char* encodedLetters[], int size) {
  char* encodedText = malloc(sizeof(char) * size + 1);

  strcpy(encodedText, "");
  int tempSize = 0;

  int encodedLettersLength[256] = {0};

  for (int i = 0; i < length; i++) {
    // printf("%c %d %d %d %d %s\n", text[i], (unsigned char)text[i],  tempSize, size, length, encodedLetters[(unsigned char)text[i]]);
    strcpy(encodedText + tempSize, encodedLetters[(unsigned char)text[i]]);

    if (encodedLettersLength[(unsigned char)text[i]] == 0) {
      encodedLettersLength[(unsigned char)text[i]] = strlen(encodedLetters[(unsigned char)text[i]]);
    }

    tempSize += encodedLettersLength[(unsigned char)text[i]];
  }

  return encodedText;
}

char* decode_text(char* encodedText, int encodedFileLength, TreeNode tree) {
  TreeNode root = tree;

  char* decodedText = malloc(sizeof(char) + 2);

  int size = 2;
  int tempSize = 0;
  for (int i = 0; i < encodedFileLength; i++) {
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

      decodedText[tempSize++] = (unsigned char)tree->letter;

      tree = root;
    }
  }

  decodedText[tempSize++] = '\0';

  return decodedText;
}

// sacar
int kk = 1;

void encode_tree(TreeNode tree, char* encodedTree, char* letters) {
  if (tree == NULL) {
    return;
  }
  char* aux = malloc(sizeof(char) * 2);

  if (tree->left == NULL && tree->right == NULL) {
    strcat(encodedTree, "1");

    letters[kk] = (unsigned char)tree->letter;
    kk++;
  } else {
    strcat(encodedTree, "0");
  }

  encode_tree(tree->left, encodedTree, letters);
  encode_tree(tree->right, encodedTree, letters);
  free(aux);
}

TreeNode decode_tree(char* encodedTree, int* encodedTreePos, char* leafs, int* leafsPos) {
  TreeNode newNode = new_node('\0', 0);

  // if (encodedTree[*encodedTreePos] == '\0' || leafs[*leafsPos] == '\0') {
  //   return newNode;
  // }

  if (encodedTree[*encodedTreePos] == '0') {
    *encodedTreePos = *encodedTreePos + 1;
    newNode->left = decode_tree(encodedTree, encodedTreePos, leafs, leafsPos);
    newNode->right = decode_tree(encodedTree, encodedTreePos, leafs, leafsPos);
  } else {
    *encodedTreePos = *encodedTreePos + 1;
    newNode->letter = (unsigned char)leafs[*leafsPos];
    *leafsPos = *leafsPos + 1;
  }
  return newNode;
}

void split(char* encodedTree, char** decodedTree, char** leafs) {
  if (encodedTree) {
    (*decodedTree) = strtok_r(encodedTree, "\n", leafs);
  }
}
