#include "main.h"

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

void parse() {
    program();
}

void program() {
    block();
    expect(".");
}

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
