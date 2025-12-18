#include <iostream>

#include "lox.h"
// #include "scanner.h"
// #include "token.h"
// #include "expr.h"
// #include "parser.h"
// #include "printer.h"

int main(int argc, char** argv){
    if(argc > 2){
        std::cerr << "Usage: " << argv[0] << " [script]\n";
        exit(EXIT_FAILURE);
    }
    else if(argc == 2){
        Lox::runFile(argv[1]);
    }
    else{
        Lox::runPrompt();
    }

    return 0;
}