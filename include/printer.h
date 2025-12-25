#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include "expr.h"
struct ASTPrinter : public ExprVisitor {
    void visitBinary(const Binary* expr) override;
    void visitGrouping(const Grouping* expr) override;
    void visitLiteral(const Literal* expr) override;
    void visitUnary(const Unary* expr) override;
    void visitVariable(const Variable* expr) override;

    virtual ~ASTPrinter() = default;
};

#endif //ASTPRINTER_H