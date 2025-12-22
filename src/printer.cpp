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

    if(std::holds_alternative<std::nullptr_t>(val)){
        return;
    }
    if(std::holds_alternative<bool>(val)){
        std::cout << std::boolalpha << std::get<bool>(val);
        return;
    }
    std::visit([](const auto& x){
        std::cout << x;
    }, val);
}

void ASTPrinter::visitUnary(const Unary* expr) {
    ASTPrinter printer;

    std::cout << '(';
    std::cout << expr->m_op.lexeme();
    expr->m_right->accept(printer);
    std::cout << ')';
}