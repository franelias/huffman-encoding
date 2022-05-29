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

void find_letters_path(TreeNode node, char prevPath[], char* results[]) {
  if (!node)
    return;

  char* newPath = malloc(sizeof(char) * strlen(prevPath) + 2);

  strcpy(newPath, prevPath);
  if (node->left) {
    strcat(newPath, "0");
    find_letters_path(node->left, newPath, results);
  }

  if (node->letter != '\0') {
    results[(unsigned char)node->letter] = malloc(sizeof(char) * strlen(newPath) + 1);
    strcpy(results[(unsigned char)node->letter], newPath);
  }
  strcpy(newPath, prevPath);
  if (node->right) {
    strcat(newPath, "1");
    find_letters_path(node->right, newPath, results);
  }
  free(newPath);
}

char* encode_text(char* text, int length, char* encodeLetters[]) {
  int size = length;
  int used = 0;
  char* encodedText = malloc(sizeof(char) * size);

  strcpy(encodedText, "");

  for (int i = 0; i < length; i++) {
    used += strlen(encodeLetters[(unsigned char)text[i]]);
    if (size <= used) {
      size = (int)used * 1.1;
      encodedText = realloc(encodedText, sizeof(char) * size);
    }

    strcat(encodedText, encodeLetters[(unsigned char)text[i]]);
  }
  strcat(encodedText, "\0");

  return encodedText;
}

char* decode_text(char* encodedText, int encodedFileLength, TreeNode tree) {
  TreeNode root = tree;

  char* decodedText = malloc(sizeof(char) + 2);

  strcpy(decodedText, "");
  int size = 1;

  for (int i = 0; i < strlen(encodedText); i++) {
    if (encodedText[i] == '0') {
      tree = tree->left;
    } else {
      tree = tree->right;
    }

    if (tree->left == NULL && tree->right == NULL) {
      if (size <= strlen(decodedText) + 1) {
        size = (int)((strlen(decodedText) + 2) * 1.1);
        decodedText = realloc(decodedText, sizeof(char) * size);
      }

      char aux[2];
      aux[0] = tree->letter;
      aux[1] = '\0';

      strcat(decodedText, aux);

      tree = root;
    }
  }

  strcat(decodedText, "\0");

  return decodedText;
}

void encode_tree(TreeNode tree, char* encodedTree, char* letters) {
  if (tree == NULL) {
    return;
  }
  char* aux = malloc(sizeof(char) * 2);

  if (tree->left == NULL && tree->right == NULL) {
    strcat(encodedTree, "1");

    aux[0] = tree->letter;
    aux[1] = '\0';

    strcat(letters, aux);
  } else {
    strcat(encodedTree, "0");
  }

  encode_tree(tree->left, encodedTree, letters);
  encode_tree(tree->right, encodedTree, letters);
  free(aux);
}

TreeNode decode_tree(char* encodedTree, int* encodedTreePos, char* leafs, int* leafsPos) {
  TreeNode newNode = new_node('\0', 0);

  if (encodedTree[*encodedTreePos] == '\0' || leafs[*leafsPos] == '\0') {
    return newNode;
  }

  if (encodedTree[*encodedTreePos] == '0') {
    *encodedTreePos = *encodedTreePos + 1;
    newNode->left = decode_tree(encodedTree, encodedTreePos, leafs, leafsPos);
    newNode->right = decode_tree(encodedTree, encodedTreePos, leafs, leafsPos);
  } else {
    *encodedTreePos = *encodedTreePos + 1;
    newNode->letter = leafs[*leafsPos];
    *leafsPos = *leafsPos + 1;
  }
  return newNode;
}

void split(char* encodedTree, char** decodedTree, char** leafs) {
  if (encodedTree) {
    (*decodedTree) = strtok_r(encodedTree, "\n", leafs);
  }
}

void print_arbol(TreeNode tree) {
  if (tree == NULL) {
    return;
  }
  print_arbol(tree->left);
  printf("%c\n", tree->letter);
  print_arbol(tree->right);
}

// strncpy