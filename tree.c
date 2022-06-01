#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

TreeNode new_node(char letter, int weight) {
  TreeNode temp = malloc(sizeof(node));
  temp->left = temp->right = NULL;
  temp->weight = weight;
  temp->letter = (unsigned char)letter;
  return temp;
}

int cmpfunc(const void* a, const void* b) {
  return (*(TreeNode*)a)->weight > (*(TreeNode*)b)->weight;
}

TreeNode* build_letters_array(char* fileContent, int contentLength, int* lettersAmount) {
  // unsigned int amountAux = 0;
  // int aux[256] = {0};
  // for (int letterPos = 0; letterPos < contentLength; letterPos++) {
  //   // si esta insertando en un nuevo lugar incrementar la cantidad
  //   if (!aux[(unsigned char)fileContent[letterPos]])
  //     amountAux++;
  //   aux[(unsigned char)fileContent[letterPos]]++;
  // }

  // TreeNode* array = malloc(sizeof(TreeNode) * amountAux);
  // for (int i = 0, j = 0; i < 256; i++) {
  //   if (aux[i]) {
  //     array[j++] = new_node(i, aux[i]);
  //   }
  // }

  // qsort(array, amountAux, sizeof(TreeNode), cmpfunc);
  // *lettersAmount = amountAux;

  int letters[256] = {0};

  for (int i = 0; i < contentLength; i++) {
    if (!letters[(unsigned char)fileContent[i]]) {
      (*lettersAmount)++;
    }

    letters[(unsigned char)fileContent[i]]++;
  }

  TreeNode* array = malloc(sizeof(TreeNode) * (*lettersAmount));
  for (int i = 0, j = 0; i < 256; i++) {
    if (letters[i]) {
      array[j++] = new_node(i, letters[i]);
    }
  }

  qsort(array, (*lettersAmount), sizeof(TreeNode), cmpfunc);

  return array;
}

TreeNode fuse_trees(int weight, TreeNode left, TreeNode right, char letter) {
  TreeNode newNode = malloc(sizeof(node));
  newNode->weight = weight;
  newNode->left = left;
  newNode->right = right;
  newNode->letter = letter;
  return newNode;
}

void destroy_tree(TreeNode* tree) {
  if (*tree) {
    TreeNode left = (*tree)->left, right = (*tree)->right;
    destroy_tree(&left);
    free(*tree);
    *tree = NULL;
    destroy_tree(&right);
  }
}

void print_arbol(TreeNode tree) {
  if (tree == NULL) {
    return;
  }
  print_arbol(tree->left);
  if (tree->left == NULL && tree->right == NULL) {
    printf("%d %d\n", (unsigned char)tree->letter, tree->weight);
  }

  print_arbol(tree->right);
}