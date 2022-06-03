#ifndef __DECODE_H_
#define __DECODE_H_
#include "lists.h"
#include "tree.h"
void decode_file(char *file);

/*
    decode_tree : char* int* char* int* -> TreeNode
    A partir de un arbol codificado y el valor de las hojas
    arma y devuelve el arbol decoficado.
*/
TreeNode decode_tree(char *encodedTree, int *encodedTreePos, char *leafs, int *leafsPos);

/*
    decode_tree_aux: char* -> TreeNode
    Función auxiliar intermedia que llamara a decode_tree con los datos que necesita
*/
TreeNode decode_tree_aux(char *encodedTree);

/*
    decode_text: char*, int, TreeNode, int* -> char*
    A partir de un texto codificado, su largo y su árbol de Huffman, decodifica el texto
    y guarda su largo en [decodedFileLen].
*/
char *decode_text(char *encodedText, int encodedFileLength, TreeNode tree, int *decodedFileLen);

#endif