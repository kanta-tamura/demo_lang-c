#include "main.h"

char* source;
Token* token;

void print_token() {
    Token* cur = token;
    while (cur->kind != TK_EOF) {
        char token[64] = "";
        strncpy(token, cur->str, cur->len);
        switch (cur->kind) {
        case TK_KEY:
            printf("%-10s:%s\n", token, "予約語");
            break;
        case TK_PUNCT:
            printf("%-10s:%s\n", token, "記号");
            break;
        case TK_IDENT:
            printf("%-10s:%s\n", token, "名前");
            break;
        case TK_NUM:
            printf("%-10s:%s\n", token, "整数");
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
    source = read_file(argv[1]);
    token = tokenize(source);
    print_token();
    return 0;
}