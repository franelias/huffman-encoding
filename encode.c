#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encode.h"
#include "common.h"
#include "io.h"
#include "lists.h"
#include "tree.h"

TreeNode generate_huffman_tree(List letters, int length)
{
  TreeNode newTree, huffmanTree;
  List firstNode, secondNode;
  int weight;

  while (length > 1)
  {
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

void find_letters_path(TreeNode node, char prevPath[], char *paths[], int *encodedLength)
{
  if (!node)
    return;

  char *newPath = malloc(sizeof(char) * strlen(prevPath) + 2);

  strcpy(newPath, prevPath);
  if (node->left)
  {
    strcat(newPath, "0");
    find_letters_path(node->left, newPath, paths, encodedLength);
  }

  if (!node->left && !node->right)
  {
    int pathLength = strlen(newPath);

    paths[(unsigned char)node->letter] = malloc(sizeof(char) * pathLength + 1);
    strcpy(paths[(unsigned char)node->letter], newPath);

    *encodedLength += pathLength * node->weight;
  }

  strcpy(newPath, prevPath);

  if (node->right)
  {
    strcat(newPath, "1");
    find_letters_path(node->right, newPath, paths, encodedLength);
  }
  free(newPath);
}

char *encode_text(char *text, int textLen, int encodedLen, char *paths[])
{
  int pathsLength[256] = {0};
  int tempLength = 0;

  char *encodedText = malloc(sizeof(char) * encodedLen + 1);
  strcpy(encodedText, "");

  for (int i = 0; i < textLen; i++)
  {
    strcpy(encodedText + tempLength, paths[(unsigned char)text[i]]);

    if (pathsLength[(unsigned char)text[i]] == 0)
    {
      pathsLength[(unsigned char)text[i]] = strlen(paths[(unsigned char)text[i]]);
    }

    tempLength += pathsLength[(unsigned char)text[i]];
  }

  return encodedText;
}

void serialize_tree(TreeNode tree, char *serializedTree, char *letters, int *lettersCount)
{
  if (tree == NULL)
  {
    return;
  }

  if (tree->left == NULL && tree->right == NULL)
  {
    strcat(serializedTree, "1");

    letters[(*lettersCount)++] = tree->letter;
  }
  else
  {
    strcat(serializedTree, "0");
  }

  serialize_tree(tree->left, serializedTree, letters, lettersCount);
  serialize_tree(tree->right, serializedTree, letters, lettersCount);
}

char *encode_tree(TreeNode tree, int lettersAmount, int *encodedTreeLen)
{
  int serializedTreeLen = lettersAmount * 2 - 1;

  char *serializedTree = malloc(sizeof(char) * serializedTreeLen); // cuanto es el largo del arbol
  strcpy(serializedTree, "");

  char *letters = malloc(sizeof(char) * lettersAmount);
  strcpy(letters, "\n");

  int *lettersCount = malloc(sizeof(int));
  *lettersCount = 1;

  serialize_tree(tree, serializedTree, letters, lettersCount);

  *encodedTreeLen = serializedTreeLen + lettersAmount;

  char *encodedTree = malloc(sizeof(char) * (*encodedTreeLen) + 1);

  strcpy(encodedTree, serializedTree);
  for (int i = 0; i < *lettersCount + 1; i++)
  {
    encodedTree[strlen(serializedTree) + i] = letters[i];
  }

  encodedTree[*encodedTreeLen + 1] = '\0';

  free(serializedTree);
  free(letters);

  return encodedTree;
}

void generate_output_files(char *fileName, char *encodedText, char *encodedTree, int encodedTextLen, int encodedTreeLen)
{
  char *outputFileName = encoded_file_name(fileName);
  char *treeFileName = tree_file_name(fileName);

  int *implodedTextLen = malloc(sizeof(int));

  char *implodedText = implode(encodedText, encodedTextLen, implodedTextLen);

  writefile(outputFileName, implodedText, *implodedTextLen);
  writefile(treeFileName, encodedTree, encodedTreeLen);

  free(outputFileName);
  free(treeFileName);
  free(implodedText);
  free(implodedTextLen);

  // void* pointers[4] = {outputFileName, treeFileName, implodedText, implodedTextLen};

  // free_all(pointers, 4);
}

void encode_file(char *file)
{
  int *contentLen = malloc(sizeof(int));
  int *lettersAmount = malloc(sizeof(int));
  int *encodedLen = malloc(sizeof(int));
  int *encodedTreeLen = malloc(sizeof(int));
  char *paths[256] = {};

  *lettersAmount = 0;
  *encodedLen = 0;
  *encodedTreeLen = 0;

  char *fileContent = readfile(file, contentLen);

  TreeNode *nodesArray = build_letters_array(fileContent, *contentLen, lettersAmount);
  List treeList = array_to_list(nodesArray, *lettersAmount);

  TreeNode huffmanTree = generate_huffman_tree(treeList, *lettersAmount);

  find_letters_path(huffmanTree, "", paths, encodedLen);

  char *encodedText = encode_text(fileContent, *contentLen, *encodedLen, paths);
  char *encodedTree = encode_tree(huffmanTree, *lettersAmount, encodedTreeLen);

  generate_output_files(file, encodedText, encodedTree, *encodedLen, *encodedTreeLen + 1);

  // free(contentLen);
  // free(lettersAmount);
  // free(encodedLen);
  // free(encodedTreeLen);
  // free(fileContent);
  // free(nodesArray);

  // destroy_tree(&huffmanTree);

  // void *pointers[7] = {fileContent, contentLength, encodedText, encodedTree, lettersInOrder, lettersAmount, encodedTreeWithLetters};

  // free_all(pointers, 7);
  // free_all((void **)paths, 256);
}