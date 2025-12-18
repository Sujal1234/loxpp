#ifndef SCANNER_H
#define SCANNER_H

#include <string_view>
#include <vector>
#include <unordered_map>

#include "token.h"

class Scanner{
    public:
        Scanner(std::string_view source);
        
        std::vector<Token> scanTokens();
    private:
        std::string_view m_source {};
        std::vector<Token> m_tokens {};

        static std::unordered_map<std::string_view, TokenType> keywordMap;
        
        size_t m_start {0};
        size_t m_current {0};
        size_t m_line {1};
        
        bool isAtEnd();
        /**
         * Consumes a character if it matches the expected one.
         */
        bool match(char expected);
        /**
         * Consumes a character.
         */
        char advance();
        /**
         * Returns the current character.
         */
        char peek();
        /**
         * Returns the next character.
         */
        char peekNext();
        void scanToken();
        /**
         * Adds a token to the vector of tokens.
         */
        void addToken(TokenType type, Token::Literal literal);
        void addToken(TokenType type);

        void readString();
        void readNumber();
        void readIdentifier();
        

};

#endif //SCANNER_H