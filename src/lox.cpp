#include <iostream>
#include <fstream>

#include "lox.h"
#include "scanner.h"
#include "parser.h"
#include "printer.h"

namespace Lox{

static bool hadError {false};

void runFile(const std::string filePath){
    std::cout << "Running file " << filePath << "\n";

    std::ifstream f {filePath};
    std::string src;

    std::string line;
    while(std::getline(f, line)){
        src += line;
    }

    Scanner scanner{src};
    std::vector<Token> tokens = scanner.scanTokens();

    // for(auto& tok : tokens){
    //     std::cout << tok.lexeme() << " ";
    // }
    // std::cout << "\n";

    Parser parser{tokens};
    ExprPtr expr = parser.parse();

    if(hadError){
        std::cerr << "Parser encountered an error\n";
        return;
    }

    // print the AST
    ASTPrinter printer;
    expr->accept(printer);
    std::cout << '\n';

    if(hadError){
        exit(EXIT_FAILURE);
    }
}

void runPrompt(){
    while(1){
        std::cout << ">> ";
        std::string inp;
        std::getline(std::cin, inp);

        if(inp == "quit()" || std::cin.eof()){
            std::cout << std::endl;
            return;
        }
        hadError = false;
    }
}

static void report(int line, std::string where, std::string_view msg){
    std::cerr << "[line " << line << "] Error " << where << ": " << msg << '\n';
    hadError = true;
}

void error(int line, std::string msg){
    report(line, "", msg);
}

void error(Token token, std::string msg) {
    if(token.type() == TokenType::EOF_) {
        report(token.line(), "at end",  msg);
    }
    else {
        report(token.line(), "at '" + token.lexeme() + "'", msg);
    }
}
};