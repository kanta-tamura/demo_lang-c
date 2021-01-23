#include "main.h"

// create new token
static Token* new_token(TokenKind kind, Token* cur, char* str, int len) {
    Token* tok = calloc(1, sizeof(Token));
    tok->kind = kind;
    tok->str  = str;
    tok->len  = len;
    cur->next = tok;
    return tok;
}

// 'p' の先頭と 'q' の内容が一致するかどうかを判定する。
static bool starts_with(char* p, char* q) {
    return memcmp(p, q, strlen(q)) == 0;
}

// 予約語かどうかを判定する。
static bool is_keyword(char* p) {
    static char* kw[] = {
      "begin", "end", "if", "then", "while", "do", "return",
      "function", "var", "const", "odd", "write", "writeln",
    };
    
    for (int i = 0; i < sizeof(kw) / sizeof(*kw); i++) {
        if (strncmp(p, kw[i], strlen(kw[i])) == 0) {
            return true;
        }
    }
    return false;
}

// 'path' ファイルの内容をトークンに分割する。
Token* tokenize(char* path) {
    char* p = read_file(path);
    
    Token head; head.next = NULL;
    Token* cur = &head;
    
    while (*p) {
        // Skip whitespace characters.
        if (isspace(*p)) {
            p++;
            continue;
        }
        
        // Multi-letter punctuator
        if (starts_with(p, "<>") || starts_with(p, "<=") ||
            starts_with(p, ">=") || starts_with(p, ":=")) {
            cur = new_token(TK_PUNCT, cur, p, 2);
            p += 2;
            continue;
        }
        
        // Single-letter punctuator
        if (strchr("+-*/()=<>,.;", *p)) {
            cur = new_token(TK_PUNCT, cur, p++, 1);
            continue;
        }
        
        // key-word
        if (is_keyword(p)) {
            cur = new_token(TK_KEY, cur, p, 0);
            char* q = p;
            while (isalpha(*p)) { p++; }
            cur->len = p - q;
            continue;
        }
        
        // Integer literal
        if (isdigit(*p)) {
            cur = new_token(TK_NUM, cur, p, 0);
            char* q = p;
            strtol(p, &p, 10); // 数値格納
            cur->len = p - q;
            continue;
        }
        
        // Identifier
        if (isalpha(*p)) {
            cur = new_token(TK_IDENT, cur, p, 0);
            char* q = p;
            while (isalnum(*p)) { p++; }
            cur->len = p - q;
            continue;
        }
    }
    
    new_token(TK_EOF, cur, p, 0);
    return head.next;
}

// 'path' ファイルの中身を char* に格納
static char* read_file(char* path) {
    // open 'path' file
    FILE* fp;
    if ( ( fp = fopen(path, "r") ) == NULL ) {
        fprintf(stderr, "Can't open file: %s", path);
        exit(EXIT_FAILURE);
    }
    
    // バッファーへの書き込み用にストリームをオープン
    char* buf;
    size_t buflen;
    FILE* out = open_memstream(&buf, &buflen);
    
    // fp の中身をすべて out に格納
    for (;;) {
        char buf2[4096];
        int n = fread(buf2, 1, sizeof(buf2), fp);
        if (n == 0)
            break;
        fwrite(buf2, 1, n, out);
    }
    
    fclose(fp);
    
    // buf, buflen のサイズを更新
    fflush(out);
    
    if (buflen == 0 || buf[buflen - 1] != '\n')
        fputc('\n', out);
    fputc('\0', out);
    
    // buf, buflen のサイズを更新
    fclose(out);
    
    return buf;
}

// トークンに分割したものを出力する。
void debug_print_token(Token* tok) {
    Token* cur = tok;
    int i = 0;
    while (cur->kind != TK_EOF) {
        // export token string
        char token[64] = "";
        strncpy(token, cur->str, cur->len);
        
        switch (cur->kind) {
        case TK_KEY:
            printf("%3d:  %-10s:%s\n", i, token, "予約語");
            break;
        case TK_PUNCT:
            printf("%3d:  %-10s:%s\n", i, token, "記号");
            break;
        case TK_IDENT:
            printf("%3d:  %-10s:%s\n", i, token, "名前");
            break;
        case TK_NUM:
            printf("%3d:  %-10s:%s\n", i, token, "整数");
            break;
        case TK_EOF:
            break;
        }
        cur = cur->next;
        i++;
    }
}
