program        → declaration* EOF
declaration    → varDecl | statement

varDecl        → "var" IDENTIFIER ("=" expression)? ";"
block -> "{" declaration* "}"

statement      → printStmt | ifStmt | exprStmt | block | whileStmt | forStmt
printStmt      → "print" expression ";"
exprStmt       → expression ";"
ifStmt         → "if" "(" expression ")" statement ("else" statement)?
whileStmt      → "while" "(" expression ")" statement
forStmt        → "for" "(" (varDecl | exprStmt | ";") expression? ";" expression? ")"

expression     → assignment
assignment     → IDENTIFIER "=" assignment | logical_or

logic_or       → logic_and ("or" logic_and)*
logic_and      → equality ("and" equality)*

equality       → comparison ( ( "!=" | "==" )   comparison ) *  (Left associative)
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term ) *  (Left associative)
term           → factor ( ( "-" | "+" ) factor ) *
factor         → unary ( ( "/" | "*" ) unary ) *  (Left associative)
unary          → ( "!" | "-" ) unary | primary
primary        → NUMBER | STRING | "true" |  "false" | "nil" | "(" expression ")" | IDENTIFIER