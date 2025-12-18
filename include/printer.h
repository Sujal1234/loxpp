#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "expr.h"
struct ASTPrinter : public ExprVisitor {
    virtual void visitBinary(const Binary* expr) override;
    virtual void visitGrouping(const Grouping* expr) override;
    virtual void visitLiteral(const Literal* expr) override;
    virtual void visitUnary(const Unary* expr) override;

    virtual ~ASTPrinter() = default;
};

#endif //ASTPRINTER_H