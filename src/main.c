#include "main.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no input file");
        exit(EXIT_FAILURE);
    }
    tokenize(argv[1]);
    return 0;
}