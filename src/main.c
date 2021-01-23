#include "main.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no input file");
        exit(EXIT_FAILURE);
    }
    char* source = read_file(argv[1]);
    printf("%s", source);
    return 0;
}