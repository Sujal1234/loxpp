#ifndef LOX_H
#define LOX_H

#include <string>

#include "expr.h"
#include "token.h"

namespace Lox{
void runFile(const std::string& filePath);
void runPrompt();
void error(int line, const std::string& msg);
void error(Token token, const std::string& msg);
// std::string printTree(ExprPtr expr);
};
#endif //LOX_H