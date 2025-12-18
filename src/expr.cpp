#include "expr.h"

bool isTruthy(Token::Literal literal){
    if(std::holds_alternative<bool>(literal)){
        return std::get<bool>(literal);
    }
    else{
        return true;
    }
}