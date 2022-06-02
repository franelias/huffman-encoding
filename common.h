#ifndef __COMMON_H_
#define __COMMON_H_

char *original_name(char *fileName);
char *encoded_file_name(char *fileName);
char *tree_file_name(char *fileName);
char *decoded_file_name(char *fileName);
void free_all(void **pointers, int amount);

#endif