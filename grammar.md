program        → statement* EOF ;
statement      → exprStmt | printStmt ;
exprStmt       → expression ";" ;
printStmt      → "print" expression ";" ;

expression     → equality ;  
equality       → comparison ( ( "!=" | "==" )   comparison ) * ;  (Left associative)
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term ) * ;  (Left associative)
term           → factor ( ( "-" | "+" ) factor ) * ;  
factor         → unary ( ( "/" | "*" ) unary ) * ;  (Left associative)
unary          → ( "!" | "-" ) unary  
               | primary ;  
primary        → NUMBER | STRING | "true" |  "false" | "nil"  
               | "(" expression ")" ;