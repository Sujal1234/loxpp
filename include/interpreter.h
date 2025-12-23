#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "expr.h"
#include "stmt.h"
#include <vector>

struct Interpreter : public ExprVisitor, public StmtVisitor {
    Token::Literal m_val {nullptr};

    void visitBinary(const Binary* expr) override;
    void visitGrouping(const Grouping* expr) override;
    void visitLiteral(const Literal* expr) override;
    void visitUnary(const Unary* expr) override;

    void visitExprStmt(const ExprStmt& stmt) override;
    void visitPrintStmt(const PrintStmt& stmt) override;

    Token::Literal getVal(const Expr& expr);
    void execute(const Stmt& stmt);
    void interpret(const std::vector<StmtPtr>& statements);

    virtual ~Interpreter() = default;
};

struct LoxRuntimeError{
    Token token;
    std::string msg;
    LoxRuntimeError(Token tok, std::string message): token{tok}, msg{message}{};
};

#endif // INTERPRETER_H