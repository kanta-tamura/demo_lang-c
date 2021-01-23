#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TK_KEY,     // 予約語(Keyword)
    TK_PUNCT,   // 区切り文字(Punctuators)
    TK_IDENT,   // 名前(Identifier)
    TK_NUM,     // 数値(Numeric literals)
    TK_EOF,     // End-of-file markers
} TokenKind;

//
// tokenize.c
//

// TODO: change static
char* read_file(char* path);
