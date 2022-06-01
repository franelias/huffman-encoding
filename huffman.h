#ifndef __HUFFMAN_H_
#define __HUFFMAN_H_

#include "lists.h"
#include "tree.h"

/*
    A partir de una lista de nodos, genera un arbol de huffman del mismo
*/
TreeNode generate_huffman_tree(List letters, int length);

/*
    A partir de un arbol de huffman, recorre el arbol inorden para guardar en
    un array de punteros el string codificado de cada letra
*/
void find_letters_path(TreeNode tree, char *arr, int top, char **results);

/*
A partir de un texto y el largo del mismo, devuelve un puntero de char con las letras codificadas
*/
char *encode_text(char *text, int length, char **encodeLetters, int size);

/*
    A partir de un texto codificado, su largo  y su arbol decodificado, decodifica el texto
*/
char *decode_text(char *encodedText, int encodedFileLength, TreeNode tree);

/*
    A partir de un arbol, recorre el arbol en preorden
     y guarda en un puntero de char el arbol codificado y en otro puntero a char
     el orden de aparicion de las letras
*/
void encode_tree(TreeNode tree, char *encodedTree, char *lettersInOrder);

/*
    A partir de un texto codificado, el valor de las hojas y dos punteros a int que funcionaran como contadores
    arma y devuelve el arbol decoficado
*/
TreeNode decode_tree(char *encodedTree, int *encodedTreePos, char *leafs, int *leafsPos);

/*
    A partir del contenido del archivo .tree, separa el texto en 2:
        - en el arbol codificado
        - las letras del arbol
*/
void split(char *encodedTree, char **decodedTree, char **leafs);
void printCodes(TreeNode tree, int *arr, int top);
#endif