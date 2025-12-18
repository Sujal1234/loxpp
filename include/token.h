#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

// enum class TokenType;
enum class TokenType{
    //Single character tokens
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA,
    DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    //One or two character tokens
    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

    //Literals
    IDENTIFIER, STRING, NUMBER,

    //Keywords
    AND, OR, THIS, CLASS, IF, ELSE, TRUE, FALSE, NIL, FUN, FOR,
    PRINT, RETURN, SUPER, VAR, WHILE,

    EOF_
};

class Token{
    public:
        using Literal = std::variant<std::nullptr_t, std::string_view, double, bool>;

        Token() = default;
        Token(TokenType type, std::string lexeme, Literal literal, int line);

        static std::string tokenTypeToString(TokenType type);
        std::string printToken() const;
        TokenType type() const;
        Literal literal() const;
        std::string lexeme() const;
        int line() const;

    private:
        TokenType m_type {};
        std::string m_lexeme {};
        Literal m_literal {nullptr}; // `Literal` is not the struct defined in expr.h
        int m_line {};
}; //class Token

#endif //TOKEN_H