#ifndef __DECODE_H_
#define __DECODE_H_
#include "lists.h"
#include "tree.h"
void decode_file(char *file);

/*
    A partir de un texto codificado, el valor de las hojas y dos punteros a int que funcionaran como contadores
    arma y devuelve el arbol decoficado
*/
TreeNode decode_tree(char *encodedTree, int *encodedTreePos, char *leafs, int *leafsPos);

TreeNode decode_tree_aux(char *encodedTree);

/*
    A partir de un texto codificado, su largo  y su arbol decodificado, decodifica el texto
*/
char *decode_text(char *encodedText, int encodedFileLength, TreeNode tree, int *a);
#endif