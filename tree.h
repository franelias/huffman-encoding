#ifndef __TREE_H_
#define __TREE_H_

typedef struct _node {
  char letter;
  int weight;
  struct _node *left;
  struct _node *right;
} node;

typedef node *TreeNode;

/*
    Crea un nodo nuevo de arbol a partir de una caracteres y un peso
     (en caso de las hojas sera la frecuencia de las caracteres)
 */
TreeNode new_node(char letter, int weight);

/*
  Crea un array de nodos de arboles (los que seran las hojas).
  Para hacerlo usa un array con el texto, el largo del mismo,
  y un puntero para devolver la cantidad de caracteres distintos
 */
TreeNode *build_letters_array(char *fileContent, int contentLength, int *lettersAmount);

/*
 A partir de un peso dado, y dos nodos, devuelve un nuevo nodo con los nodos viejos como hijos
 */
TreeNode fuse_trees(int weight, TreeNode left, TreeNode right, char letter);

/*
  A partir de un puntero a nodo, libera la memoria del arbol
 */
void destroy_tree(TreeNode* tree);

#endif
