#include "main.h"

Token* token;

void print_token() {
    Token* cur = token;
    while (cur->kind != TK_EOF) {
        switch (cur->kind) {
        case TK_KEY:
            printf("%s\n", "Keyword");
            break;
        case TK_PUNCT:
            printf("%s\n", "Punctuators");
            break;
        case TK_IDENT:
            printf("%s\n", "Identifier");
            break;
        case TK_NUM:
            printf("%s\n", "Numeric literals");
            break;
        case TK_EOF:
            break;
        }
        cur = cur->next;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "no input file");
        exit(EXIT_FAILURE);
    }
    token = tokenize(argv[1]);
    print_token();
    return 0;
}