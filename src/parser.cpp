#include "parser.h"
#include "expr.h"
#include "lox.h"

ExprPtr Parser::expression() {
    return equality();
}

ExprPtr Parser::equality() {
    ExprPtr expr = comparison();
    
    // comparison ( ( "!=" | "==" )   comparison )* ;
    while(match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        Token op = previous();
        ExprPtr right = comparison();
        expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
    }
    return expr;
}

ExprPtr Parser::comparison() {
    // term ( ( ">" | ">=" | "<" | "<=" ) term )*
    ExprPtr expr = term();

    while(match({
        TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL
    }))
    {
        Token op = previous();
        ExprPtr right = term();
        expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
    }
    return expr;
}

ExprPtr Parser::term() {
    // factor ( ( "-" | "+" ) factor )*
    ExprPtr expr = factor();

    while(match({
        TokenType::MINUS, TokenType::PLUS
    })) 
    {
        Token op = previous();
        ExprPtr right = factor();
        expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
    }
    return expr;
}

ExprPtr Parser::factor() {
    // unary ( ( "/" | "*" ) unary )*
    ExprPtr expr = unary();

    while(match({
        TokenType::SLASH, TokenType::STAR
    })) 
    {
        Token op = previous();
        ExprPtr right = unary();
        expr = std::make_unique<Binary>(std::move(expr), std::move(right), op);
    }
    return expr;
}

ExprPtr Parser::unary() {
    // ( "!" | "-" ) unary
    if(match({
        TokenType::BANG, TokenType::MINUS
    }))
    {
        Token op = previous();
        ExprPtr expr = unary();
        return std::make_unique<Unary>(op, std::move(expr));
    }

    return primary();
}

ExprPtr Parser::primary() {
    // NUMBER | STRING | "true" |  "false" | "nil"  
    //    | "(" expression ")" ;
    if(match({
        TokenType::NUMBER, TokenType::STRING, TokenType::TRUE, TokenType::FALSE, TokenType::NIL
    }))
    {
        Token::Literal lit = previous().literal();
        return std::make_unique<Literal>(lit);
    }

    if(match({TokenType::LEFT_PAREN})) {
        auto expr = expression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after expression.");
        return std::make_unique<Grouping>(std::move(expr));
    }
    else{
        throw error(peek(), "Expect expression.");
    }
}

Token Parser::consume(TokenType type, std::string msg) {
    if(check(type)){
        return advance();
    }

    throw error(peek(), msg);
}

Parser::ParseError Parser::error(Token token, std::string msg) {
    Lox::error(token, msg);
    return ParseError{};
}

bool Parser::match(std::vector<TokenType> types) {
    for(auto type : types){
        if(check(type)){
            // If one type matches then consume the token and return true
            advance();
            return true;
        }
    }
    return false;
}

Token Parser::advance() {
    if(!isAtEnd()) current++;
    return previous();
}

Token Parser::peek() {
    return m_tokens[current];
}

Token Parser::previous() {
    return m_tokens[current-1];
}

bool Parser::check(TokenType type) {
    if(isAtEnd()) return false;
    return peek().type() == type;
}

bool Parser::isAtEnd() {
    return peek().type() == TokenType::EOF_;
}

void Parser::synchronise(){
    Token prev = advance();

    while(!isAtEnd()){
        if(prev.type() == TokenType::SEMICOLON) return;

        // If one of these tokens is encountered, it is probably the start of a new statement.
        switch (peek().type()) {
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
            default:
                break;
      }
      advance();
    }
}

ExprPtr Parser::parse() {
    try{
        return expression();
    }
    catch (ParseError error){
        return nullptr;
    }
}