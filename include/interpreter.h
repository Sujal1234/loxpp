#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "expr.h"
#include "stmt.h"
#include "state.h"
#include <vector>

struct Interpreter : public ExprVisitor, public StmtVisitor {
    State state;
    Token::Literal m_val {nullptr};

    Interpreter() = default;
    Interpreter(State* state_){
        state.parentState = state_;
    }

    void visitBinary(const Binary* expr) override;
    void visitGrouping(const Grouping* expr) override;
    void visitLiteral(const Literal* expr) override;
    void visitUnary(const Unary* expr) override;
    void visitVariable(const Variable* expr) override;
    void visitAssignment(const Assignment* expr) override;
    void visitLogic(const Logic* expr) override;

    void visitExprStmt(const ExprStmt& stmt) override;
    void visitPrintStmt(const PrintStmt& stmt) override;
    void visitDeclStmt(const DeclStmt& stmt) override;
    void visitBlockStmt(const BlockStmt& stmt) override;
    void visitIfStmt(const IfStmt& stmt) override;
    
    Token::Literal getVal(const Expr& expr);
    void execute(const Stmt& stmt);
    void interpret(const std::vector<StmtPtr>& statements);

    virtual ~Interpreter() = default;
};

#endif // INTERPRETER_H