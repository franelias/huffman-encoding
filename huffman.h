#ifndef __HUFFMAN_H_
#define __HUFFMAN_H_

#include "lists.h"
#include "tree.h"

TreeNode generate_huffman_tree(List nodes, int amount);

void tree_in_order(TreeNode n, char *prevPath, char **results);

char *encode_text(char *text, int length, char **encodeLetters);

void encode_tree(TreeNode tree, char *encodedTree);

char *decode_text(char *encoded_text, TreeNode decoded_tree);

#endif
