#include <iostream>
#include <fstream>

#include "lox.h"
#include "scanner.h"
#include "parser.h"
#include "printer.h"
#include "interpreter.h"

namespace Lox{

static bool hadError {false};
static bool hadRuntimeError {false};
static Interpreter interpreter{};

static void run(const std::string& source){
    Scanner scanner{source};
    std::vector<Token> tokens = scanner.scanTokens();

    Parser parser{tokens};
    auto statements = parser.parse();

    if(hadError){
        std::cerr << "Parser encountered an error\n";
        return;
    }

    interpreter.interpret(statements);
}

void runFile(const std::string& filePath){
    std::cout << "Running file " << filePath << "\n";

    std::ifstream f {filePath};
    std::string src;

    std::string line;
    while(std::getline(f, line)){
        src += line + "\n";
    }

    run(src);

    if(hadError) exit(65);
    if(hadRuntimeError) exit(70);
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
        run(inp);
        hadError = false;
    }
}

static void report(int line, const std::string& where, const std::string& msg){
    std::cerr << "[line " << line << "] Error " << where << ": " << msg << '\n';
    hadError = true;
}

void error(int line, const std::string& msg){
    report(line, "", msg);
}

void error(const Token& token, const std::string& msg) {
    if(token.type() == TokenType::EOF_) {
        report(token.line(), "at end",  msg);
    }
    else {
        report(token.line(), "at '" + token.lexeme() + "'", msg);
    }
}

void runtimeError(LoxRuntimeError& error){
    std::cerr << "Error at '" << error.token.lexeme() << "' : ";
    std::cerr << error.msg << "\n[line " << error.token.line() << "]\n";
    hadRuntimeError = true;
}
};