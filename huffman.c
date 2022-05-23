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

    // secondNode->next=NULL;
    // secondNode->tree=newTree;

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
    // printf("%c %s\n", n->data.letter, newPath);
    results[node->letter] = malloc(sizeof(char) * strlen(newPath) + 1);
    strcpy(results[node->letter], newPath);
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
    used += strlen(encodeLetters[text[i]]);
    if (size <= used) {
      size = (int)used * 1.1;
      encodedText = realloc(encodedText, sizeof(char) * size);
    }

    strcat(encodedText, encodeLetters[text[i]]);
  }
  strcat(encodedText, "\0");

  return encodedText;
}

void encode_tree(TreeNode tree, char* encodedTree, char* letters) {
  if (tree == NULL) {
    return;
  }

  if (tree->left == NULL && tree->right == NULL) {
    strcat(encodedTree, "1");

    char* aux = malloc(sizeof(char) * 2);
    aux[0] = tree->letter;
    aux[1] = '\0';

    strcat(letters, aux);
    free(aux);
  } else {
    strcat(encodedTree, "0");
  }

  encode_tree(tree->left, encodedTree, letters);
  encode_tree(tree->right, encodedTree, letters);
}

char* decode_text(char* encodedText, TreeNode tree) {
  TreeNode root = tree;

  char* decoded_text = malloc(sizeof(char) + 1);

  strcpy(decoded_text, "");

  for (int i = 0; i < strlen(encodedText); i++) {
    if (tree->left == NULL && tree->right == NULL) {
      decoded_text = realloc(decoded_text, sizeof(char) * (strlen(decoded_text) + 1));

      // handlear error realloc
      char aux[2];
      aux[0] = tree->letter;
      aux[1] = '\0';

      strcat(decoded_text, aux);

      tree = root;
    }

    if (encodedText[i] == '0') {
      tree = tree->left;
    } else {
      tree = tree->right;
    }
  }

  strcat(decoded_text, "\0");

  return decoded_text;
}

// wip
TreeNode decode_tree(char* encodedTree, int* encodedTreePos, char* encodedLeafs, int* encodedLeafsPos) {
  TreeNode newNode = malloc(sizeof(TreeNode));
  newNode->weight = 0;
  if (encodedTree[*encodedTreePos] == '0') {
    *encodedTreePos++;
    newNode->left = decode_tree(encodedTree, encodedTreePos, encodedLeafs, encodedLeafsPos);
    *encodedTreePos++;
    newNode->right = decode_tree(encodedTree, encodedTreePos, encodedLeafs, encodedLeafsPos);
    newNode->letter = '\0';
  } else {
    *encodedTreePos++;
    newNode->right = newNode->left = NULL;
    newNode->letter = encodedLeafs[*encodedLeafsPos];
    *encodedLeafsPos++;
  }
  return newNode;
}
