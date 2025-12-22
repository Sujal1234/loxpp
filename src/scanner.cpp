#include <vector>
#include <string>

#include "scanner.h"
#include "token.h"
#include "lox.h"

std::unordered_map<std::string_view, TokenType> Scanner::keywordMap{
    {"and", TokenType::AND},
    {"or", TokenType::OR},
    {"this", TokenType::THIS},
    {"class", TokenType::CLASS},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"nil", TokenType::NIL},
    {"fun", TokenType::FUN},
    {"for", TokenType::FOR},
    {"print", TokenType::PRINT},
    {"return", TokenType::RETURN},
    {"super", TokenType::SUPER},
    {"var", TokenType::VAR},
    {"while", TokenType::WHILE}
};

Scanner::Scanner(std::string_view source)
    : m_source {source}
    {}

std::vector<Token> Scanner::scanTokens(){
    while(!isAtEnd()){
        //At the beginning of the next lexeme
        m_start = m_current;
        scanToken();
    }

    //Add an EOF_ token after all the tokens
    m_tokens.push_back(Token(TokenType::EOF_, "", nullptr, m_line));
    return m_tokens;
}

bool Scanner::isAtEnd(){
    return m_current >= m_source.length();
}

void Scanner::scanToken(){
    char c = advance();

    switch (c)
    {
        // Single character tokens
        case '(': addToken(TokenType::LEFT_PAREN);  break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE);  break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA);       break;
        case '.': addToken(TokenType::DOT);         break;
        case '-': addToken(TokenType::MINUS);       break;
        case '+': addToken(TokenType::PLUS);        break;
        case ';': addToken(TokenType::SEMICOLON);   break;
        case '*': addToken(TokenType::STAR);        break;

        //Double character tokens
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        
        //Slash token. Check if it's for a comment or the division symbol
        case '/':
            if(match('/')){
                //Comment
                while(!isAtEnd() && peek() != '\n') advance();
            }
            else{
                addToken(TokenType::SLASH);
            }
            break;
        
        //Whitespace
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n': m_line++; break;

        //Strings
        case '"': readString(); break;

        //Number or unhandled character
        default:
            if(isdigit(c)){
                readNumber();
            }
            else if(isalpha(c)){
                readIdentifier();
            }
            else{
                Lox::error(m_line, "Unexpected character.");
                break;
            }
    }
}

//Consume one character and return it
char Scanner::advance(){
    return m_source.at(m_current++);
}

char Scanner::peek(){
    if(isAtEnd()) return '\0';
    return m_source[m_current];
}

char Scanner::peekNext(){
    if(m_current + 1 >= m_source.length()) return '\0';
    return m_source[m_current+1];
}

//Push a new token to the tokens vector
void Scanner::addToken(TokenType type, Token::Literal literal){
    std::string_view textSV = m_source.substr(m_start, m_current - m_start);
    std::string text = std::string{textSV.data(), m_current - m_start};
    m_tokens.push_back(Token(type, text, literal, m_line));
}

//Overloading addToken for tokens which are non-literal tokens
void Scanner::addToken(TokenType type){
    addToken(type, nullptr);
}

bool Scanner::match(char expected){
    if(isAtEnd()) return false;
    if(m_source.at(m_current) != expected){
        return false;
    }
    //Consume only if it matches
    m_current++;
    return true;
}

void Scanner::readString(){
    while(!isAtEnd() && peek() != '"'){
        if(peek() == '\n') m_line++;
        advance();
    }

    if(isAtEnd()){
        Lox::error(m_line, "Unterminated string.");
    }
    //Consume quotation mark - "
    advance();

    auto str = std::string(m_source.substr(m_start+1, m_current-m_start-2));
    addToken(TokenType::STRING, str);
}

void Scanner::readNumber(){
    while(isdigit(peek())) advance();

    //Decimal point checking
    if(peek() == '.' && isdigit(peekNext())){
        //Consume the '.'
        advance();

        while(isdigit(peek())) advance();
    }

    std::string_view str = m_source.substr(m_start, m_current - m_start);
    double num = std::strtod(str.data(), nullptr);
    addToken(TokenType::NUMBER, num);
}

void Scanner::readIdentifier(){
    //alnum instead of alpha because the identifier can
    //have a digit in it after the first character
    while(isalnum(peek())) advance();

    std::string_view str = m_source.substr(m_start, m_current - m_start);

    TokenType type;
    if(keywordMap.find(str) != keywordMap.end()){
        //keyword matched
        type = keywordMap[str];
    }
    else type = TokenType::IDENTIFIER;
    
    switch(type) {
        case TokenType::NIL:
            addToken(type, nullptr);
            return;
        case TokenType::TRUE:
            addToken(type, true);
            return;
        case TokenType::FALSE:
            addToken(type, false);
            return;
        default:
            break;
    }

    addToken(type);
}