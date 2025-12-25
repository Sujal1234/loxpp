#include "state.h"
#include "lox.h"

void State::defineVar(const std::string& name, Token::Literal val){
    variables[name] = val;
}

Token::Literal State::get(const Token& name){
    auto it = variables.find(name.lexeme());
    if(it != variables.end()){
        return it->second;
    }
    throw LoxRuntimeError(name, "Undefined variable '" + name.lexeme() + "'.");
}