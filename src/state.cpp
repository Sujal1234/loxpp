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
    if(parentState){
        return parentState->get(name);
    }
    throw LoxRuntimeError(name, "Undefined variable '" + name.lexeme() + "'.");
}

void State::assign(const Token& name, const Token::Literal& value){
    auto it = variables.find(name.lexeme());
    if(it != variables.end()){
        it->second = value;
        return;
    }
    if(parentState){
        parentState->assign(name, value);
    }
    else{
        throw LoxRuntimeError(name, "Undefined variable '" + name.lexeme() + "'.");
    }
}