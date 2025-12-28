#include <iostream>
#include "printer.h"
#include "expr.h"

void ASTPrinter::printAST(const Expr& expr){
    expr.accept(*this);
}

void ASTPrinter::visitBinary(const Binary* expr) {
    std::cout << '(';
    printAST(*expr->m_left);
    std::cout << " " << expr->m_op.lexeme() << " ";
    printAST(*expr->m_right);
    std::cout << ')';
}

void ASTPrinter::visitGrouping(const Grouping* expr) {
    std::cout << '(';
    printAST(*expr->m_expr);
    std::cout << ')';
}

void ASTPrinter::visitLiteral(const Literal* expr) {
    Token::Literal val = expr->m_value;
    printLiteral(val);
}

void ASTPrinter::visitUnary(const Unary* expr) {
    std::cout << '(';
    std::cout << expr->m_op.lexeme();
    printAST(*expr->m_right);
    std::cout << ')';
}

void ASTPrinter::visitVariable(const Variable* expr){
    std::cout << expr->m_identifier.lexeme();
}

void ASTPrinter::visitAssignment(const Assignment* expr){
    std::cout << expr->m_name.lexeme() << " = ";
    printAST(*expr->m_value);
}