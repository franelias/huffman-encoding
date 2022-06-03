#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "common.h"
#include "io.h"
#include "lists.h"
#include "tree.h"

TreeNode decode_tree(char *encodedTree, int *encodedTreePos, char *leafs, int *leafsPos)
{
  TreeNode newNode = new_node('\0', 0);

  if (encodedTree[*encodedTreePos] == '\n')
  {
    return newNode;
  }

  if (encodedTree[*encodedTreePos] == '0')
  {
    *encodedTreePos = *encodedTreePos + 1;
    newNode->left = decode_tree(encodedTree, encodedTreePos, leafs, leafsPos);
    newNode->right = decode_tree(encodedTree, encodedTreePos, leafs, leafsPos);
  }
  else
  {
    newNode->letter = leafs[*leafsPos];
    *encodedTreePos = *encodedTreePos + 1;
    *leafsPos = *leafsPos + 1;
  }

  return newNode;
}

TreeNode decode_tree_aux(char *encodedTree)
{
  int *encodedTreePos = malloc(sizeof(int));
  int *leafsPos = malloc(sizeof(int));

  *encodedTreePos = 0;
  *leafsPos = 0;
  int i = 0;

  for (i = 0; encodedTree[i] != '\n'; i++)
    ;
  i++;

  TreeNode decodedTree = decode_tree(encodedTree, encodedTreePos, encodedTree + i, leafsPos);
  free(encodedTreePos);

  return decodedTree;
}

char *decode_text(char *encodedText, int encodedFileLength, TreeNode tree, int *decodedFileLen)
{
  TreeNode root = tree;

  char *decodedText = malloc(sizeof(char) + 2);

  int size = 1;
  int tempSize = 0;
  for (int i = 0; i < encodedFileLength; i++)
  {
    if (tree->left == NULL && tree->right == NULL)
    {
      if (size <= tempSize + 1)
      {
        size = (int)((tempSize + 2) * 1.5);
        decodedText = realloc(decodedText, sizeof(char) * size);
      }

      decodedText[tempSize++] = tree->letter;

      tree = root;
    }

    if (encodedText[i] == '0')
    {
      tree = tree->left;
    }
    else
    {
      tree = tree->right;
    }
  }

  decodedText[tempSize] = '\0';

  *decodedFileLen = tempSize;

  return decodedText;
}

void decode_file(char *file)
{
  int *implodedFileLen = malloc(sizeof(int));
  int *encodedFileLen = malloc(sizeof(int));
  int *decodedFileLen = malloc(sizeof(int));
  int *encodedTreeLen = malloc(sizeof(int));

  char *originalName = original_name(file);
  char *treeFileName = tree_file_name(originalName);

  char *implodedFile = readfile(file, implodedFileLen);
  char *encodedTree = readfile(treeFileName, encodedTreeLen);

  char *encodedFile = explode(implodedFile, *implodedFileLen, encodedFileLen);

  TreeNode decodedTree = decode_tree_aux(encodedTree);

  char *decodedText = decode_text(encodedFile, *encodedFileLen, decodedTree, decodedFileLen);

  writefile(decoded_file_name(originalName), decodedText, *decodedFileLen);

  // char* decodedTree;
  // char* leafs;

  // int* decodedFileLength = malloc(sizeof(int));

  // destroy_tree(&decodedTreeWL);

  // void* pointers[11] = {implodedFileLength, encodedTreeLength, encodedFileLength, implodedFile, encodedFile, decodedTree, contador1, contador2, decodedText, treeFileName};

  // free_all(pointers, 11);
}