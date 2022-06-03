#ifndef __COMMON_H_
#define __COMMON_H_
/*
    original_name: char* -> char*
    toma el nombre de un archivo ".hf" y devuelve el mismo sin ".hf"
*/
char *original_name(char *fileName);

/*
    encoded_file_name: char* -> char*
    toma el nombre de un archivo y devuelve el mismo con ".hf"
*/
char *encoded_file_name(char *fileName);

/*
    tree_file_name: char* -> char*
    toma el nombre de un archivo y delvuelve el mismo con ".tree"
*/
char *tree_file_name(char *fileName);

/*
    decoded_file_name: char* -> char*
    toma el nombre de un archivo y devuelve el mismo con ".dec"
*/
char *decoded_file_name(char *fileName);

/*
    free_all: void**, int ->void
    toma un array de  punteros y su largo, y libera la memoria de cada elemento
*/
void free_all(void **pointers, int amount);

#endif