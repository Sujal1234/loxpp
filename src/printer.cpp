#include <iostream>
#include "printer.h"
#include "expr.h"

void ASTPrinter::visitBinary(const Binary* expr) {
    ASTPrinter printer;
    std::cout << '(';
    expr->m_left->accept(printer);
    std::cout << " " << expr->m_op.lexeme() << " ";
    expr->m_right->accept(printer);
    std::cout << ')';
}

void ASTPrinter::visitGrouping(const Grouping* expr) {
    ASTPrinter printer;
    std::cout << '(';
    expr->m_expr->accept(printer);
    std::cout << ')';
}

void ASTPrinter::visitLiteral(const Literal* expr) {
    Token::Literal val = expr->m_value;

    printLiteral(val);
}

void ASTPrinter::visitUnary(const Unary* expr) {
    ASTPrinter printer;

    std::cout << '(';
    std::cout << expr->m_op.lexeme();
    expr->m_right->accept(printer);
    std::cout << ')';
}

void ASTPrinter::visitVariable(const Variable* expr){
    std::cout << expr->m_identifier.lexeme();
}