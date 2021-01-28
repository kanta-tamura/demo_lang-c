#include "main.h"

Node* new_node(NodeKind kind) {
    Node* node = calloc(1, sizeof(Node));
    node->kind = kind;
    return node;
}

Node* new_binary(NodeKind kind, Node* lhs, Node* rhs) {
    Node* node = new_node(kind);
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node* new_num(int val) {
    Node* node = new_node(ND_NUM);
    node->val = val;
    return node;
}

Node* new_ident(char* buf) {
    Node* node = new_node(ND_IDENT);
    node->buf = buf;
    return node;
}

void program();
void block();
void const_decl();
void var_decl();
void func_decl();
void statement();
void condition();
void expression();
void term();
void factor();

// parser
void parse() {
    program();
}

// program = block, "."
void program() {
    block();
    expect(".");
}

// block
// = statement
// | constDecl, statement
// | varDecl, statement
// | funcDecl, statement
// ;
void block() {
    while (true) {
        if (consume("const")) {
            const_decl();
            continue;
        }
        if (consume("var")) {
            var_decl();
            continue;
        }
        if (consume("function")) {
            func_decl();
            continue;
        }
        break;
    }
    statement();
}

void const_decl() {
    while (true) {
        expect_ident();      // 文字列を返す
        expect("=");
        expect_number();     // 数値を返す
        if (consume(";")) break;
        expect(",");
    }
}

void var_decl() {
    while (true) {
        expect_ident();      // 文字列を返す
        if (consume(";")) break;
        expect(",");
    }
}

void func_decl() {
    expect_ident();          // 文字列を返す
    expect("(");
    while (true) {
        expect_ident();      // 文字列を返す
        if (consume(")")) break;
        expect(",");
    }
    block();
    expect(";");
}

void statement() {
    if (tok->kind == TK_IDENT) {
        expect_ident();      // 文字列を返す
        expect(":=");
        expression();
    }
    else if (consume("begin")) {
        while (true) {
            statement();
            if (consume("end")) break;
            expect(";");
        }
    }
    else if (consume("if")) {
        condition();
        expect("then");
        statement();
    }
    else if (consume("while")) {
        condition();
        expect("do");
        statement();
    }
    else if (consume("return")) {
        expression();
    }
    else if (consume("write")) {
        expression();
    }
    else if (consume("writeln")) {

    }
    // do nothing
}

void condition() {
    if (consume("odd")) {
        expression();
        return;
    }
    expression();
    if (consume("=") || consume("<>") || consume("<") ||
        consume(">") || consume("<=") || consume(">="))
        expression();
    // else ERROR
}

void expression() {
    if (consume("+") || consume("-")) term();
    else term();
    while (true) {
        if (consume("+") || consume("-")) term();
        else break;
    }
}

void term() {
    factor();
    while (true) {
        if (consume("*") || consume("/")) term();
        else break;
    }
}

void factor() {
    if (tok->kind == TK_IDENT) {
        expect_ident();      // 文字列を返す
        if (consume("(")) {
            while (!consume(")")) {
                expression();
                if (consume(")")) break;
                expect(",");
            }
        }
    }
    else if (tok->kind == TK_NUM) {
        expect_number();     // 数値を返す
    }
    else if (consume("(")) {
        expression();
        expect(")");
    }
}
