#ifndef STMT_H
#define STMT_H
#include "expr.h"
#include <memory>


struct ExprStmt;
struct PrintStmt;
struct DeclStmt;
struct StmtVisitor;

struct Stmt{
    virtual void accept(StmtVisitor& visitor) const = 0;
    virtual ~Stmt() = default;
};

struct StmtVisitor{
    virtual void visitExprStmt(const ExprStmt& stmt) = 0;
    virtual void visitPrintStmt(const PrintStmt& stmt) = 0;
    virtual void visitDeclStmt(const DeclStmt& stmt) = 0;

    virtual ~StmtVisitor() = default;
};

struct ExprStmt : public Stmt{
    ExprPtr m_expr;
    ExprStmt(ExprPtr expr) : m_expr{std::move(expr)}{};

    void accept(StmtVisitor& visitor) const override{
        visitor.visitExprStmt(*this);
    }
    ~ExprStmt() override = default;
};

struct PrintStmt : public Stmt{
    ExprPtr m_expr;
    PrintStmt(ExprPtr expr) : m_expr{std::move(expr)}{};

    void accept(StmtVisitor& visitor) const override{
        visitor.visitPrintStmt(*this);
    }
    ~PrintStmt() override = default;
};

struct DeclStmt : public Stmt{
    Token m_name;
    ExprPtr m_init;
    DeclStmt(Token&& name, ExprPtr init)
    : m_name{std::move(name)}
    , m_init{std::move(init)}{}

    void accept(StmtVisitor& visitor) const override{
        visitor.visitDeclStmt(*this);
    }
    ~DeclStmt() override = default;
};

using StmtPtr = std::unique_ptr<Stmt>;
using ExprStmtPtr = std::unique_ptr<ExprStmt>;
using PrintStmtPtr = std::unique_ptr<PrintStmt>;
using DeclStmtPtr = std::unique_ptr<DeclStmt>;
#endif // STMT_H