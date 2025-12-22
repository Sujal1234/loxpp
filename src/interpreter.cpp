#include <iostream>
#include "interpreter.h"
#include "lox.h"

Token::Literal getVal(Interpreter& itpr, Expr& expr){
    expr.accept(itpr);
    return itpr.m_val;
}

static void checkNumber(const Token::Literal& literal, const Token& operand){
    if(!std::holds_alternative<double>(literal)){
        throw LoxTypeError(operand, "Operand must be a number.");
    }
}
static void checkNumbers(const Token::Literal& left, const Token::Literal& right, const Token& operand){
    if(!std::holds_alternative<double>(left) || !std::holds_alternative<double>(right)){
        throw LoxTypeError(operand, "Operands must be numbers.");
    }
}

void Interpreter::visitBinary(const Binary* expr){
    auto lval = getVal(*this, *(expr->m_left));
    auto rval = getVal(*this, *(expr->m_right));

    switch (expr->m_op.type())
    {
    case TokenType::PLUS: {
        if(std::holds_alternative<double>(lval) && std::holds_alternative<double>(rval)){
            m_val = std::get<double>(lval) + std::get<double>(rval);
        }
        else if(std::holds_alternative<std::string>(lval) && std::holds_alternative<std::string>(rval)){
            m_val = std::get<std::string>(lval) + std::get<std::string>(rval);
        }
        else{
            m_val = nullptr;
            throw LoxTypeError(expr->m_op, "Operands are not of the correct type.");
        }
    }break;

    // Arithmetic
    case TokenType::MINUS: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) - std::get<double>(rval);
    }break;
    case TokenType::SLASH: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) / std::get<double>(rval);
    }break;
    case TokenType::STAR: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) * std::get<double>(rval);
    }break;

    // Comparisons
    case TokenType::GREATER: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) > std::get<double>(rval);
    }break;
    case TokenType::GREATER_EQUAL: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) >= std::get<double>(rval);
    }break;
    case TokenType::LESS: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) < std::get<double>(rval);
    }break;
    case TokenType::LESS_EQUAL: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) <= std::get<double>(rval);
    }break;
    case TokenType::BANG_EQUAL: {
        m_val = lval != rval;
    }break;
    case TokenType::EQUAL_EQUAL: {
        m_val = lval == rval;
    }break;

    default: {
        m_val = nullptr;
    }break;
    }
}

void Interpreter::visitGrouping(const Grouping* expr){
    m_val = getVal(*this, *(expr->m_expr));
}

void Interpreter::visitLiteral(const Literal* expr){
    m_val = expr->m_value;
}
void Interpreter::visitUnary(const Unary* expr){
    auto val = getVal(*this, *(expr->m_right));

    switch(expr->m_op.type()){
        case TokenType::MINUS: {
            checkNumber(val, expr->m_op);
            m_val = -std::get<double>(val);
        }break;

        case TokenType::BANG: {
            m_val = !Token::isTruthy(val);
        }break;
        default: {
            m_val = nullptr;
        }break;
    }
}

void Interpreter::interpret(Expr& expr){
    try{
        Token::Literal value = getVal(*this, expr);
        printLiteral(value);
        std::cout << '\n';
    }
    catch(LoxTypeError err){
        Lox::runtimeError(err);
    }
}