@page grammar Embedded ML Grammar
@brief The formal grammar of the Embedded ML language is the guideline of the parser to transform tokens into AST. It may not have a one-to-one relationship with the AST.

@section expressions Expressions
The language run-time will interprets and computes an expression to produce a value. Embedded ML have a number of unary and binary expressions with different precedence. The grammar do not directly specify the precedence relationship, please look at [Precedence and Associativity](@ref precedence) for more information.

```.ebnf
expr = constant
     | prefix_op expr
     | expr infix_op expr
```
 
@section const Constants
```.ebnf
constant = float_literal
         | "true"
         | "false"
         | "()"
float_literal = digit+ ("." digit+)?
```

@section prefix Prefix Operators
```.ebnf
prefix_op = "-"
          | "!"
```

@section infix Infix operators
```.ebnf
infix_op = "+" | "-" | "*" | "-" | "==" | "!=" | "<" | "<=" | ">" | ">="
```