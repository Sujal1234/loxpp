program        → declaration* EOF
declaration    → varDecl | block | statement

varDecl        → "var" IDENTIFIER ("=" expression)? ";"
block -> "{" declaration* "}"

statement      → printStmt | exprStmt
printStmt      → "print" expression ";"
exprStmt       → expression ";"

expression     → assignment
assignment     → IDENTIFIER "=" assignment | equality
equality       → comparison ( ( "!=" | "==" )   comparison ) *  (Left associative)
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term ) *  (Left associative)
term           → factor ( ( "-" | "+" ) factor ) *
factor         → unary ( ( "/" | "*" ) unary ) *  (Left associative)
unary          → ( "!" | "-" ) unary | primary
primary        → NUMBER | STRING | "true" |  "false" | "nil" | "(" expression ")" | IDENTIFIER