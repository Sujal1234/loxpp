#include "token.h"
#include <string>
#include <sstream>
#include <iostream>

// Token::Token(const TokenType type, const std::string_view lexeme, const int line)
//     : m_type{type}
//     , m_lexeme{lexeme}
//     , m_line{line}
//     {}

Token::Token(TokenType type, std::string lexeme, Literal literal, int line)
    : m_type{type}
    , m_lexeme{lexeme}
    , m_literal {literal}
    , m_line{line}
    {}

std::string Token::tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUAL: return "BANG_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::AND: return "AND";
        case TokenType::OR: return "OR";
        case TokenType::THIS: return "THIS";
        case TokenType::CLASS: return "CLASS";
        case TokenType::IF: return "IF";
        case TokenType::ELSE: return "ELSE";
        case TokenType::TRUE: return "TRUE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::NIL: return "NIL";
        case TokenType::FUN: return "FUN";
        case TokenType::FOR: return "FOR";
        case TokenType::PRINT: return "PRINT";
        case TokenType::RETURN: return "RETURN";
        case TokenType::SUPER: return "SUPER";
        case TokenType::VAR: return "VAR";
        case TokenType::WHILE: return "WHILE";
        case TokenType::EOF_: return "EOF_";
        default: return "UNKNOWN";
    }
}

std::string Token::printToken() const{
    std::stringstream buf {};
    buf << tokenTypeToString(m_type) << " " << m_lexeme << " ";
    std::visit([&buf](const auto& ele) {buf << ele;}, m_literal);
    return buf.str(); 
}

TokenType Token::type() const {
    return m_type;
}
std::string Token::lexeme() const {
    return m_lexeme;
}
Token::Literal Token::literal() const {
    return m_literal;
}
int Token::line() const {
    return m_line;
}

bool Token::isTruthy(const Literal& literal){
    if(std::holds_alternative<bool>(literal)){
        return std::get<bool>(literal);
    }
    else{
        return true;
    }
}

void printLiteral(const Token::Literal& val){
    if(std::holds_alternative<std::nullptr_t>(val)){
        std::cout << "NIL";
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