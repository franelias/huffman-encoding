huffman: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c -o huff

valgrindC: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c
	- valgrind ./a.out C test_files/fceia.jpg

valgrindD: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c
	- valgrind ./a.out D test_files/fceia.jpg.hf

test: encode.c encode.h tree.c  decode.c decode.h common.c common.h tree.h io.c io.h lists.c lists.h tests_lists.c tests_tree.c tests_huffman_encode.c tests_huffman_decode.c
	- gcc tests_tree.c tree.c -o test
	- ./test

	- gcc tests_lists.c tree.c lists.c  -o test
	- ./test

	- gcc tests_huffman_encode.c encode.c tree.c lists.c  common.c io.c -o test
	- ./test

	- gcc tests_huffman_decode.c decode.c encode.c tree.c lists.c common.c io.c -o test
	- ./test

	-	rm -rf ./test