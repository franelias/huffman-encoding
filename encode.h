#ifndef __ENCODE_H_
#define __ENCODE_H_

#include "lists.h"
#include "tree.h"

void encode_file(char *file);

/*
    A partir de una lista de nodos, genera un arbol de huffman del mismo
*/
TreeNode generate_huffman_tree(List letters, int length);

/*
    A partir de un arbol de huffman, recorre el arbol inorden para guardar en
    un array de punteros el string codificado de cada letra
*/
void find_letters_path(TreeNode node, char prevPath[], char *paths[], int *encodedLength);

/*
A partir de un texto y el largo del mismo, devuelve un puntero de char con las letras codificadas
*/
char *encode_text(char *text, int textLen, int encodedLen, char *paths[]);

/*
    A partir de un arbol, recorre el arbol en preorden
     y guarda en un puntero de char el arbol codificado y en otro puntero a char
     el orden de aparicion de las letras
*/
char *encode_tree(TreeNode tree, int lettersAmount, int *encodedTreeLen);

#endif