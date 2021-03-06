#include "main.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no input file\n");
        exit(EXIT_FAILURE);
    }
    // tokenize and print results
    tok = debug_tokenize(argv[1]);
    Node* node = parse();
    printf("Success\n");
    return 0;
}