#ifndef __ENCODE_H_
#define __ENCODE_H_

#include "lists.h"
#include "tree.h"

/*
    encode_file: char* -> void
    Funcion que se encarga de llamar a las funciones necesarias para codificar
     el contenido del archivo y lo guarda en sus respectivos archivos
     (.tree donde estara el arbol codficado, y .hf donde estara el contenido del texto codificado)
*/
void encode_file(char *file);

/*
    generate_huffman_tree: List, int -> TreeNode
    A partir de una lista de nodos, genera un arbol de huffman del mismo
*/
TreeNode generate_huffman_tree(List letters, int length);

/*
    find_letters_path: TreeNode, char* ,char**, int* ->void
    A partir de un arbol de huffman, recorre el arbol inorden para guardar en
    un array de punteros el string codificado de cada letra y el tamaño final
    del contenido del archivo codificado en binario
*/
void find_letters_path(TreeNode node, char prevPath[], char *paths[], int *encodedLength);

/*
    encode_text: char*, int, int, char** -> char*
    A partir de un texto y el largo del mismo, devuelve un puntero de char con las letras codificadas
*/
char *encode_text(char *text, int textLen, int encodedLen, char *paths[]);

/*
encode_tree: TreeNode, int, int* -> char*

    A partir de un arbol, recorre el arbol en preorden
     y devuelve el arbol codificado junto a sus hojas. Tambien guarda el largo del mismo.
*/
char *encode_tree(TreeNode tree, int lettersAmount, int *encodedTreeLen);

#endif