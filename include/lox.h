#ifndef LOX_H
#define LOX_H

#include <string>
#include "token.h"

struct LoxRuntimeError{
    Token token;
    std::string msg;
    LoxRuntimeError(Token tok, std::string message): token{tok}, msg{message}{};
};

namespace Lox{
void runFile(const std::string& filePath);
void runPrompt();
void error(int line, const std::string& msg);
void error(Token token, const std::string& msg);
void runtimeError(LoxRuntimeError& error);
};


#endif //LOX_H