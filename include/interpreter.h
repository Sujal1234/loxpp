#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "expr.h"

struct Interpreter : public ExprVisitor {
    Token::Literal m_val {nullptr};

    virtual void visitBinary(const Binary* expr) override;
    virtual void visitGrouping(const Grouping* expr) override;
    virtual void visitLiteral(const Literal* expr) override;
    virtual void visitUnary(const Unary* expr) override;

    void interpret(Expr& expr);

    virtual ~Interpreter() = default;
};

struct LoxTypeError{
    Token token;
    std::string msg;
    LoxTypeError(Token tok, std::string message): token{tok}, msg{message}{};
};

Token::Literal getVal(Interpreter& itpr, Expr& expr);

#endif // INTERPRETER_H