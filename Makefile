encoder: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- gcc main.c huffman.c tree.c io.c lists.c
	- ./a.out

decoder: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- rm -rf decoder
	- gcc decoder.c huffman.c tree.c io.c lists.c
	- ./a.out

valgrind: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- rm -rf decoder
	- gcc decoder.c huffman.c tree.c io.c lists.c
	- valgrind ./a.out