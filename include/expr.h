#ifndef EXPR_H
#define EXPR_H

#include <variant>
#include <memory>

#include "token.h"

struct Expr;
struct Binary;
struct Grouping;
struct Literal;
struct Unary;

using ExprPtr = std::unique_ptr<Expr>;

struct ExprVisitor {
    virtual void visitBinary(const Binary* expr) = 0;
    virtual void visitGrouping(const Grouping* expr) = 0;
    virtual void visitLiteral(const Literal* expr) = 0;
    virtual void visitUnary(const Unary* expr) = 0;

    virtual ~ExprVisitor() = default;
};

struct Expr {
    Expr() = default;
    virtual ~Expr() = default;

    virtual void accept(ExprVisitor& visitor) const = 0;
};

struct Binary : public Expr {
    ExprPtr m_left {};
    ExprPtr m_right {};
    Token m_op {};

    Binary(ExprPtr left, ExprPtr right, Token op)
    : m_left{std::move(left)}
    , m_right{std::move(right)}
    , m_op{op}
    {}
    virtual ~Binary() = default;

    virtual void accept(ExprVisitor& visitor) const {
        visitor.visitBinary(this);
    }
};

struct Grouping : public Expr {
    ExprPtr m_expr {};

    Grouping(ExprPtr expr)
    : m_expr{std::move(expr)}
    {}
    virtual ~Grouping() = default;

    virtual void accept(ExprVisitor& visitor) const {
        visitor.visitGrouping(this);
    }
};

struct Literal : public Expr {
    Token::Literal m_value {};

    Literal(Token::Literal value)
    : m_value{value}
    {}
    virtual ~Literal() = default;

    virtual void accept(ExprVisitor& visitor) const {
        visitor.visitLiteral(this);
    }
};

struct Unary : public Expr {
    Token m_op {};
    ExprPtr m_right {};

    Unary(Token op, ExprPtr right)
    : m_op{op}
    , m_right{std::move(right)}
    {}
    virtual ~Unary() = default;

    virtual void accept(ExprVisitor& visitor) const {
        visitor.visitUnary(this);
    }
};

#endif //EXPR_H