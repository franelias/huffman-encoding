huffman: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c

valgrindC: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c
	- valgrind ./a.out C prueba.txt 

valgrindD: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c
	- valgrind ./a.out D prueba.txt.hf
