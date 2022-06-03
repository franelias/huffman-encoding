#ifndef __COMMON_H_
#define __COMMON_H_
/*
    quit_file_error: char* char* int*
    Funcion que hace libera los punteros, y hace exit
*/
void quit_file_error(char *fileName, char *fileContent, int *fileLength);

/*
    original_name: char* -> char*
    Toma el nombre de un archivo ".hf" y devuelve el mismo sin ".hf"
*/
char *original_name(char *fileName);

/*
    encoded_file_name: char* -> char*
    Toma el nombre de un archivo y devuelve el mismo con ".hf"
*/
char *encoded_file_name(char *fileName);

/*
    tree_file_name: char* -> char*
    Toma el nombre de un archivo y devuelve el mismo con ".tree"
*/
char *tree_file_name(char *fileName);

/*
    decoded_file_name: char* -> char*
    Toma el nombre de un archivo y devuelve el mismo con ".dec"
*/
char *decoded_file_name(char *fileName);

/*
    free_all: void** int ->void
    Toma un array de punteros con su largo, y libera la memoria de cada elemento
*/
void free_all(void **pointers, int amount);

#endif