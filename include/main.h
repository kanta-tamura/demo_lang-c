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

//
// parse.c
//

typedef enum {
    ND_ADD,     // +
    ND_SUB,     // -
    ND_MUL,     // *
    ND_DIV,     // /
    ND_EQ,      // =
    ND_LT,      // <
    ND_LE,      // <=
    ND_LR,      // <>
    ND_COMMA,   // ,
    ND_PERIOD,  // .
    ND_ASSIGN,  // :=
    ND_NUM,     // Integer
    ND_IDENT,   // Identifier
} NodeKind;

// AST node type
typedef struct Node Node;
struct Node {
    NodeKind kind;  // Node kind
    Node* lhs;      // Left-hand side
    Node* rhs;      // Right-hand side
    int val;        // Used if kind == ND_NUM
    char* buf;      // Used if kind == ND_IDENT
};

Node* parse();

