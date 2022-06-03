huffman: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c -o huff

valgrindC: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c
	- valgrind ./a.out C test_files/fceia.jpg

valgrindD: main.c encode.c decode.c tree.c io.c lists.c common.c encode.h decode.h tree.h io.h lists.h common.h
	- gcc main.c encode.c decode.c tree.c io.c lists.c common.c
	- valgrind ./a.out D test_files/fceia.jpg.hf

test: encode.c encode.h tree.c  decode.c decode.h common.c common.h tree.h io.c io.h lists.c lists.h lists_test.c tree_test.c encode_test.c decode_test.c
	- gcc tree_test.c tree.c common.c -o test
	- ./test

	- gcc lists_test.c tree.c lists.c common.c -o test
	- ./test

	- gcc encode_test.c encode.c tree.c lists.c  common.c io.c -o test
	- ./test

	- gcc decode_test.c decode.c encode.c tree.c lists.c common.c io.c -o test
	- ./test

	-	rm -rf ./test

