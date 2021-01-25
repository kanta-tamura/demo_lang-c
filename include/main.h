#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//
// tokenize.c
//

typedef enum {
    TK_KEY,     // 予約語(Keyword)
    TK_PUNCT,   // 区切り文字(Punctuators)
    TK_IDENT,   // 名前(Identifier)
    TK_NUM,     // 数値(Numeric literals)
    TK_EOF,     // End-of-file markers
} TokenKind;

typedef struct Token Token;
struct Token {
    TokenKind kind; // Token kind
    Token* next;    // Next token
    char* str;      // Token string
    int len;        // Token length
};

Token* tokenize(char* path);
Token* debug_tokenize(char* path);

static Token* new_token(TokenKind kind, Token* cur, char* str, int len);
void error_at(char* source, char* loc, char* fmt, ...);
static bool starts_with(char* p, char* q);
static bool is_keyword(char* p);
static char* read_file(char* path);
static void debug_print_token(Token* tok);

//
// parse.c
//


