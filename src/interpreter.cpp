#include "interpreter.h"

Token::Literal getVal(Expr* expr){
    Interpreter itpr;
    expr->accept(itpr);
    return itpr.m_val;
}
void Interpreter::visitBinary(const Binary* expr){
    auto lval = getVal(expr->m_left.get());
    auto rval = getVal(expr->m_right.get());

    switch (expr->m_op.type())
    {
    case TokenType::PLUS: {
        if(std::holds_alternative<double>(lval) && std::holds_alternative<double>(rval)){
            m_val = std::get<double>(lval) + std::get<double>(rval);
        }
        else if(std::holds_alternative<std::string>(lval) && std::holds_alternative<std::string>(lval)){
            m_val = std::get<std::string>(lval) + std::get<std::string>(rval);
        }
        else{
            // TODO: Throw error?
            m_val = nullptr;
        }
    }break;

    // TODO: Error handling for all of these if the type is incorrect.

    // Arithmetic
    case TokenType::MINUS: {
        m_val = std::get<double>(lval) - std::get<double>(rval);
    }break;
    case TokenType::SLASH: {
        m_val = std::get<double>(lval) / std::get<double>(rval);
    }break;
    case TokenType::STAR: {
        m_val = std::get<double>(lval) * std::get<double>(rval);
    }break;

    // Comparisons
    case TokenType::GREATER: {
        m_val = std::get<double>(lval) > std::get<double>(rval);
    }break;
    case TokenType::GREATER_EQUAL: {
        m_val = std::get<double>(lval) >= std::get<double>(rval);
    }break;
    case TokenType::LESS: {
        m_val = std::get<double>(lval) < std::get<double>(rval);
    }break;
    case TokenType::LESS_EQUAL: {
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
    m_val = getVal(expr->m_expr.get());
}

void Interpreter::visitLiteral(const Literal* expr){
    m_val = expr->m_value;
}
void Interpreter::visitUnary(const Unary* expr){
    auto val = getVal(expr->m_right.get());

    switch(expr->m_op.type()){
        case TokenType::MINUS: {
            m_val = -std::get<double>(val);
        }break;

        case TokenType::BANG: {
            m_val = !Token::isTruthy(val);
        }break;
        default: {
            // TODO: Throw error?
            m_val = nullptr;
        }break;
    }
}