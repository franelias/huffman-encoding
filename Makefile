encoder: main.c encode.c encode.h decode.c decode.h tree.c tree.h io.c io.h lists.c lists.h common.c common.h
	- gcc main.c encode.c decode.c  tree.c io.c lists.c common.c
	- ./a.out C prueba.txt

decoder: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h common.c common.h
	- gcc main.c encode.c decode.c  tree.c io.c lists.c common.c
	- ./a.out D prueba.txt.hf

valgrindC: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- rm -rf decoder
	- gcc main.c huffman.c tree.c io.c lists.c
	- valgrind ./a.out C prueba.txt 

valgrindD: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- rm -rf decoder
	- gcc main.c huffman.c tree.c io.c lists.c
	- valgrind ./a.out D prueba.txt.hf