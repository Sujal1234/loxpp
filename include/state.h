#ifndef STATE_H
#define STATE_H
#include <unordered_map>
#include <string>

#include "token.h"

class State{
private:
    std::unordered_map<std::string, Token::Literal> variables;
public:
    void defineVar(const std::string& name, Token::Literal val);
    Token::Literal get(const Token& name);
};
#endif // STATE_H