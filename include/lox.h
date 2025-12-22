#ifndef LOX_H
#define LOX_H

#include <string>

#include "expr.h"
#include "token.h"
#include "interpreter.h"

namespace Lox{
void runFile(const std::string& filePath);
void runPrompt();
void error(int line, const std::string& msg);
void error(Token token, const std::string& msg);
void runtimeError(LoxTypeError& error);
};
#endif //LOX_H