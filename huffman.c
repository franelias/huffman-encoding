#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TreeNode generate_huffman_tree(List nodes, int amount) {
  TreeNode newTree, huffmanTree;
  List firstNode, secondNode;
  int weight;

  while (amount > 1) {
    firstNode = nodes;
    secondNode = nodes->next;

    weight = firstNode->tree->weight + secondNode->tree->weight;

    newTree = fuse_trees(weight, firstNode->tree, secondNode->tree, '\0');

    nodes = nodes->next->next;

    List newNode = malloc(sizeof(nodeList));
    newNode->next = NULL;
    newNode->tree = newTree;

    free(firstNode);
    free(secondNode);

    sorted_insert(&nodes, newNode);
    amount--;
  }

  huffmanTree = nodes->tree;

  free(nodes);

  return huffmanTree;
}

void tree_in_order(TreeNode node, char prevPath[], char* results[]) {
  if (!node)
    return;
  char* newPath = malloc(sizeof(char) * strlen(prevPath) + 2);

  strcpy(newPath, prevPath);
  if (node->left) {
    strcat(newPath, "0");
    tree_in_order(node->left, newPath, results);
  }

  if (node->letter != '\0') {
    // printf("%c %s\n", n->data.letter, newPath);
    results[node->letter] = malloc(sizeof(char) * strlen(newPath) + 1);
    strcpy(results[node->letter], newPath);
  }
  strcpy(newPath, prevPath);
  if (node->right) {
    strcat(newPath, "1");
    tree_in_order(node->right, newPath, results);
  }
  free(newPath);
}

char* encode_text(char* text, int length, char* encodeLetters[]) {
  char* encodedText = malloc(sizeof(char));
  strcpy(encodedText, "");

  for (int i = 0; i < length; i++) {
    encodedText = realloc(encodedText, sizeof(char) * strlen(encodedText) + strlen(encodeLetters[text[i]]) + 1);
    strcat(encodedText, encodeLetters[text[i]]);
  }
  strcat(encodedText, "\0");

  return encodedText;
}

void encode_tree(TreeNode tree, char* encodedTree) {
  if (!tree) return;
  if (!tree->left && !tree->right) {
    encodedTree = realloc(encodedTree, sizeof(char) * strlen(encodedTree) + 1);
    strcat(encodedTree, "1");
    return;
  }
  encodedTree = realloc(encodedTree, sizeof(char) * strlen(encodedTree) + 1);
  strcat(encodedTree, "0");
  encode_tree(tree->left, encodedTree);
  encode_tree(tree->right, encodedTree);
  strcat(encodedTree, "\0");
}

char* decode_text(char* encoded_text, TreeNode decoded_tree) {
  TreeNode root = decoded_tree;

  char* decoded_text = malloc(sizeof(char) + 1);

  strcpy(decoded_text, "");

  for (int i = 0; i < strlen(encoded_text); i++) {
    if (decoded_tree->left == NULL && decoded_tree->right == NULL) {
      decoded_text = realloc(decoded_text, sizeof(char) * (strlen(decoded_text) + 1));

      // handlear error realloc
      char aux[2];
      aux[0] = decoded_tree->letter;
      aux[1] = '\0';

      strcat(decoded_text, aux);

      decoded_tree = root;
    }

    if (encoded_text[i] == '0') {
      decoded_tree = decoded_tree->left;
    } else {
      decoded_tree = decoded_tree->right;
    }
  }

  strcat(decoded_text, "\0");

  return decoded_text;
}