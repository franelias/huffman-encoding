#ifndef __ENCODE_H_
#define __ENCODE_H_

#include "lists.h"
#include "tree.h"

/*
    encode_file: char* -> void
    Función que se encarga de llamar a las funciones necesarias para codificar
    el contenido del archivo y lo guarda en sus respectivos archivos
    (.tree donde estara el árbol codficado, y .hf donde estara el contenido del texto codificado)
*/
void encode_file(char *file);

/*
    generate_huffman_tree: List int -> TreeNode
    A partir de una lista de nodos, genera un árbol de Huffman del mismo
*/
TreeNode generate_huffman_tree(List letters, int length);

/*
    find_letters_path: TreeNode char* char** int* -> void
    A partir de un árbol de Huffman, recorre el árbol y guarda en [paths]
    la codificación de cada letra y en [encodedLength] el tamaño final
    del contenido del archivo codificado en binario.
*/
void find_letters_path(TreeNode node, char prevPath[], char *paths[], int *encodedLength);

/*
    encode_text: char* int int char** -> char*
    A partir de un texto y el largo del mismo, devuelve el texto codificado con el
    las codificaciones de cada letra de [paths]
*/
char *encode_text(char *text, int textLen, int encodedLen, char *paths[]);

/*
    A partir de un árbol, lo recorre y retorna el mismo codificado junto a sus hojas.
    Guarda el largo del mismo en [encodedTreeLen]
    encode_tree: TreeNode, int, int* -> char*
*/
char *encode_tree(TreeNode tree, int lettersAmount, int *encodedTreeLen);

#endif