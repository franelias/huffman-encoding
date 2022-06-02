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

<<<<<<< HEAD
test: encode.c encode.h tree.c  decode.c decode.h common.c common.h tree.h io.c io.h lists.c lists.h tests_lists.c tests_tree.c tests_huffman_encode.c tests_huffman_decode.c
	- gcc tests_tree.c tree.c -o test
	- ./test
	
	- gcc tests_lists.c tree.c lists.c  -o test
	- ./test
	
	- gcc tests_huffman_encode.c encode.c tree.c lists.c  common.c io.c -o test
	- ./test

	- gcc tests_huffman_decode.c decode.c encode.c tree.c lists.c common.c io.c -o test
	- ./test


	-rm -rf ./test
=======
test: huffman.c huffman.h tree.c tree.h io.c io.h lists.c lists.h tests_lists.c tests_tree.c tests_huffman.c
	- gcc tests_tree.c tree.c -o test
	- ./test
	
	- gcc tests_lists.c tree.c lists.c  -o test
	- ./test

	- gcc tests_huffman.c huffman.c tree.c lists.c -o test
	- ./test

	-rm -rf ./test
>>>>>>> Test huffman encode
