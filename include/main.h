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
    int val;        // If kind is TK_NUM, its value
    int len;        // Token length
};

extern char* source;
extern Token* tok;

Token* tokenize(char* path);
Token* debug_tokenize(char* path);

bool consume(char* op);
void expect(char* op);
int expect_number();
char* expect_ident();
bool at_eof();

static Token* new_token(TokenKind kind, Token* cur, char* str, int len);
static void error_at(char* loc, char* fmt, ...);
static bool starts_with(char* p, char* q);
static int len_match_keyword(char* p);
static char* read_file(char* path);
static void debug_print_token(Token* tok);

//
// parse.c
//

void parse();
static void program();
static void block();
static void const_decl();
static void var_decl();
static void func_decl();
static void statement();
static void condition();
static void expression();
static void term();
static void factor();
