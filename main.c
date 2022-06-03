#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode.h"
#include "encode.h"
#include "io.h"

#define ENCODER_ALIAS "C"
#define DECODER_ALIAS "D"

int main(int argc, char** argv) {
  if (argc < 3) {
    exit(1);
  }

  if (strcmp(argv[1], ENCODER_ALIAS) == 0) {
    encode_file(argv[2]);
  } else if (strcmp(argv[1], DECODER_ALIAS) == 0) {
    decode_file("prueba.txt.hf");
  } else {
    printf("Invalid arguments");
  }

  return 0;
}