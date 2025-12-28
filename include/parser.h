#ifndef PARSER_H
#define PARSER_H

#include <vector>

#include "token.h"
#include "expr.h"
#include "stmt.h"

class Parser {
private:
    std::vector<Token> m_tokens;
    int current = 0;

public:
    Parser(std::vector<Token> tokens)
    : m_tokens {tokens}
    {}

    std::vector<StmtPtr> parse();

private:
    class ParseError {};

private:
    /**
     * Functions to match different types of expressions in the grammar
     */
    ExprPtr expression();
    ExprPtr assignment();
    ExprPtr equality();
    ExprPtr comparison();
    ExprPtr term();
    ExprPtr factor();
    ExprPtr unary();
    ExprPtr primary();
    StmtPtr declaration();
    StmtPtr statement();
    BlockStmtPtr block();
    DeclStmtPtr varDecl();
    PrintStmtPtr printStatement();
    ExprStmtPtr exprStatement();
    
    /**
     * Returns true if at least one of the types matches.
     */
    bool match(std::vector<TokenType> types);
    bool match(TokenType type);
    /**
     * If we are at the end then returns previous token.
     * Otherwise returns the current token and then consumes it.
     */
    Token advance();
    /**
     * Checks if we are at a token of the given type
     */
    bool check(TokenType type);
    /**
     * Checks if we are currently at an EOF token
     */
    bool isAtEnd();
    /**
     * Returns the token we are currently at.
     */
    Token peek();
    /**
     * Returns the most recently consumed token.
     */
    Token previous();
    /**
     * Consumes the token if it matches otherwise throws an error
     */
    Token consume(TokenType type, const std::string& msg);
    ParseError error(const Token& token, const std::string& msg);
    
    void synchronise();    
};
#endif // PARSER_H