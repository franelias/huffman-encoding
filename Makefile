encoder: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- gcc main.c huffman.c tree.c io.c lists.c
	- ./a.out C prueba.txt

decoder: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- gcc main.c huffman.c tree.c io.c lists.c
	- ./a.out D prueba.txt.hf

valgrindC: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- rm -rf decoder
	- gcc main.c huffman.c tree.c io.c lists.c
	- valgrind ./a.out C prueba.txt 

valgrindD: main.c huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h
	- rm -rf decoder
	- gcc main.c huffman.c tree.c io.c lists.c
	- valgrind ./a.out D prueba.txt.hf

test: huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h tests_lists.c tests_tree.c tests_huffman_encode.c tests_huffman_decode.c
	- gcc tests_tree.c tree.c -o test
	- ./test
	
	- gcc tests_lists.c tree.c lists.c  -o test
	- ./test

	- gcc tests_huffman_encode.c huffman.c tree.c lists.c -o test
	- ./test

	- gcc tests_huffman_decode.c huffman.c tree.c lists.c -o test
	- ./test

	-rm -rf ./test