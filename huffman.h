#ifndef __HUFFMAN_H_
#define __HUFFMAN_H_

#include "lists.h"
#include "tree.h"

TreeNode generate_huffman_tree(List letters, int length);

void find_letters_path(TreeNode node, char *prevPath, char **results);

char *encode_text(char *text, int length, char **encodeLetters);

char *decode_text(char *encodedText, int encodedFileLength, TreeNode tree);

void encode_tree(TreeNode tree, char *encodedTree, char *lettersInOrder);

TreeNode decode_tree(char* encodedTree, int* encodedTreePos, char* leafs, int* leafsPos);

void print_arbol(TreeNode tree);

void split(char *encodedTree, char **decodedTree, char **leafs);

#endif
