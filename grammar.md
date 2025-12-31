program        → declaration* EOF
declaration    → varDecl | statement

varDecl        → "var" IDENTIFIER ("=" expression)? ";"
block -> "{" declaration* "}"

statement      → printStmt | ifStmt | exprStmt | block
printStmt      → "print" expression ";"
exprStmt       → expression ";"
ifStmt         → "if" "(" expression ")" statement ("else" statement)?

expression     → assignment
assignment     → IDENTIFIER "=" assignment | equality
equality       → comparison ( ( "!=" | "==" )   comparison ) *  (Left associative)
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term ) *  (Left associative)
term           → factor ( ( "-" | "+" ) factor ) *
factor         → unary ( ( "/" | "*" ) unary ) *  (Left associative)
unary          → ( "!" | "-" ) unary | primary
primary        → NUMBER | STRING | "true" |  "false" | "nil" | "(" expression ")" | IDENTIFIER