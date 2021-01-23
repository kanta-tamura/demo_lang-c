#include "main.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no input file\n");
        exit(EXIT_FAILURE);
    }
    // tokenize and print results
    Token* token = tokenize(argv[1]);
    debug_print_token(token);
    return 0;
}