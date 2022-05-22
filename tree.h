#ifndef __TREE_H_
#define __TREE_H_

typedef struct _node {
  char letter;
  int weight;
  struct _node* left;
  struct _node* right;
} node;

typedef node* TreeNode;

/*
 * descripcion loca
 */
TreeNode new_node(char letter, int weight);

/*
 * descripcion loca
 */
TreeNode* read_text(char* text, int length, int* amount);

/*
 * descripcion loca
 * pasar a ingles
 */
TreeNode fuse_trees(int weight, TreeNode left, TreeNode right, char letter);

/*
 * descripcion loca
 */
void destroyTree(TreeNode tree);

#endif
