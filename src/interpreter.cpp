#include <iostream>
#include "interpreter.h"
#include "lox.h"
#include "stmt.h"
#include "token.h"

Token::Literal Interpreter::getVal(const Expr& expr){
    expr.accept(*this);
    return m_val;
}

static void checkNumber(const Token::Literal& literal, const Token& operand){
    if(!std::holds_alternative<double>(literal)){
        throw LoxRuntimeError(operand, "Operand must be a number.");
    }
}
static void checkNumbers(const Token::Literal& left, const Token::Literal& right, const Token& operand){
    if(!std::holds_alternative<double>(left) || !std::holds_alternative<double>(right)){
        throw LoxRuntimeError(operand, "Operands must be numbers.");
    }
}

void Interpreter::visitBinary(const Binary* expr){
    auto lval = getVal(*(expr->m_left));
    auto rval = getVal(*(expr->m_right));

    switch (expr->m_op.type())
    {
    case TokenType::PLUS: {
        if(std::holds_alternative<double>(lval) && std::holds_alternative<double>(rval)){
            m_val = std::get<double>(lval) + std::get<double>(rval);
        }
        else if(std::holds_alternative<std::string>(lval) && std::holds_alternative<std::string>(rval)){
            m_val = std::get<std::string>(lval) + std::get<std::string>(rval);
        }
        else{
            m_val = nullptr;
            throw LoxRuntimeError(expr->m_op, "Operands are not of the correct type.");
        }
    }break;

    // Arithmetic
    case TokenType::MINUS: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) - std::get<double>(rval);
    }break;
    case TokenType::SLASH: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) / std::get<double>(rval);
    }break;
    case TokenType::STAR: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) * std::get<double>(rval);
    }break;

    // Comparisons
    case TokenType::GREATER: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) > std::get<double>(rval);
    }break;
    case TokenType::GREATER_EQUAL: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) >= std::get<double>(rval);
    }break;
    case TokenType::LESS: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) < std::get<double>(rval);
    }break;
    case TokenType::LESS_EQUAL: {
        checkNumbers(lval, rval, expr->m_op);
        m_val = std::get<double>(lval) <= std::get<double>(rval);
    }break;
    case TokenType::BANG_EQUAL: {
        m_val = lval != rval;
    }break;
    case TokenType::EQUAL_EQUAL: {
        m_val = lval == rval;
    }break;

    default: {
        m_val = nullptr;
    }break;
    }
}

void Interpreter::visitGrouping(const Grouping* expr){
    m_val = getVal(*(expr->m_expr));
}

void Interpreter::visitLiteral(const Literal* expr){
    m_val = expr->m_value;
}
void Interpreter::visitUnary(const Unary* expr){
    auto val = getVal(*(expr->m_right));

    switch(expr->m_op.type()){
        case TokenType::MINUS: {
            checkNumber(val, expr->m_op);
            m_val = -std::get<double>(val);
        }break;

        case TokenType::BANG: {
            m_val = !Token::isTruthy(val);
        }break;
        default: {
            m_val = nullptr;
        }break;
    }
}

void Interpreter::visitVariable(const Variable* expr){
    m_val = state.get(expr->m_identifier);
}

void Interpreter::visitAssignment(const Assignment* expr){
    m_val = getVal(*expr->m_value);
    state.assign(expr->m_name, m_val);
}

void Interpreter::visitLogic(const Logic* expr){
    auto left = getVal(*expr->m_left);
    if(expr->m_op.type() == TokenType::OR){
        if(Token::isTruthy(left)){
            m_val = left;
            return;
        }
    }
    else{
        if(!Token::isTruthy(left)){
            m_val = left;
            return;
        }
    }
    m_val = getVal(*expr->m_right);
}

void Interpreter::visitExprStmt(const ExprStmt& stmt){
    getVal(*stmt.m_expr);
}

void Interpreter::visitPrintStmt(const PrintStmt& stmt){
    auto val = getVal(*stmt.m_expr);
    printLiteral(val);
    std::cout << '\n';
}

void Interpreter::visitDeclStmt(const DeclStmt& stmt){
    auto val = getVal(*stmt.m_init);
    state.defineVar(stmt.m_name.lexeme(), val);
}

void Interpreter::visitBlockStmt(const BlockStmt& stmt){
    auto blockInterpreter = Interpreter(&(this->state));
    blockInterpreter.interpret(stmt.statements);
}

void Interpreter::visitIfStmt(const IfStmt& stmt){
    auto val = getVal(*stmt.condition);
    if(Token::isTruthy(val)){
        execute(*stmt.ifBranch);
    }
    else{
        execute(*stmt.elseBranch);
    }
}

void Interpreter::visitWhileStmt(const WhileStmt& stmt){
    while(Token::isTruthy(getVal(*stmt.condition))){
        execute(*stmt.statement);
    }
}

void Interpreter::execute(const Stmt& stmt){
    stmt.accept(*this);
}

void Interpreter::interpret(const std::vector<StmtPtr>& statements){
    try{
        for(const StmtPtr& stmt : statements){
            execute(*stmt);
        }
    }
    catch(LoxRuntimeError err){
        Lox::runtimeError(err);
    }
}