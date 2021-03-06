@page grammar Embedded ML Grammar
@brief The formal grammar of the Embedded ML language is the guideline of the parser to transform tokens into [AST](@ref ast.hpp). It may not have a one-to-one relationship with the AST.

@section identifier Identifier
Identifier is a string contains alphanumerical character or "_", the first character cannot be an number.
```.ebnf
identifier = [_a-zA-Z][_a-zA-Z0-9]
```

At some place, we can annotation identifiers with an optional type annotation:
```.ebnf
typed_identifier = identifier (":" type)?
```

@section toplevel_input Toplevel Input

The embedded ML program is a list of the top level inputs. `toplevel_input` represents all of the entry points into the interpreter. These are all of the types of input that a user can put in the toplevel.

```.ebnf
toplevel_input = expr
               | definition
```

@section definition Definition
```.ebnf
definition = "let" identifier "=" expr;
```

Definitions represent let [expressions](@ref expressions) at the top level.

@section expressions Expressions
The language run-time will interprets and computes an expression to produce a value. Embedded ML have a number of unary and binary expressions with different precedence. The grammar do not directly specify the precedence relationship, please look at [Precedence and Associativity](@ref precedence) for more information.

```.ebnf
expr = constant
     | identifier
     | block
     | prefix_op expr
     | expr infix_op expr
     | group
     | "if" group expr "else" expr // If expression
     | "let" typed_identifier "=" expr ";" expr // Let binding
     | "\" (typed_identifier)+ "->" expr // Lambda expression
```

Groups have parentheses around expressions.
```.ebnf
group = "(" expr ")"
```

Blocks is a expression surrounded by curly braces.

```.ebnf
block = "{" expr "}"
```
 
@subsection const Constants
```.ebnf
constant = float_literal
         | "true"
         | "false"
         | "()"
float_literal = digit+ ("." digit+)?
```

@subsection prefix Prefix Operators
```.ebnf
prefix_op = "-"
          | "!"
```

@subsection infix Infix operators
```.ebnf
infix_op = "+" | "-" | "*" | "-" | "==" | "!=" | "<" | "<=" | ">" | ">="
```

@section type Types
We can add explicit type annotation to an Embedded ML value binding or functions.
```.ebnf
type = identifier  // Named type
     | type "->" type // Function type
     | "(" type ")"
```
