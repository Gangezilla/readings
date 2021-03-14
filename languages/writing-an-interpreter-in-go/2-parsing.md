# Parsing

## Parsers

A parser is a software component that takes input data and builds a data structure (like an AST) giving a structural representation of the input, checking for correct syntax in the process. Basically, a parser turns its input into a data structure that represents the input.

A pretty simple example of this is `JSON.parse('{"name": "Scott"}')` in JS.

In most interpreters, the internal representation of the source code is an abstract syntax tree (AST). Abstract because certain details (like semicolons, comments etc) are missing in the AST.

## Writing a parser

There are two main strategies when parsing a programming language: top-down parsing and bottom-up parsing. Top-down parsing basically starts with constructing the root node of the AST and descends, while the latter does it the other way around.

## Parsing let statements

A let statement, like `let x = 5;` binds a value (here, 5) to a given name (x).

Expressions produce values, statements don't.

The AST we're going to construct consists soley of `Node`s that are connected to each other in a tree. Some of these nodes implement the `Statement` interface and some `Expression`.

Every Monkey program is a series of statements, which we'll hold in thw `Statements` slice.

When we're storing a `let` statement, we want to have the name, the value and then the `token` as well.

The Parser has three fields, `l`, `curToken` and `peekToken`. `l` is a pointer to an instance of the lexer. `curToken` and `peekToken` act like the two pointers the lexer has, except these point to the current and next **token**, instead of the character like the lexer is.

The way the parser works:

- Read each token
- Determine what the token is
- Depending on what the token is, parse it appropriately. For example, if we get a `let` statement we parse that and validate it. For example, if we parse a `let` statement and it's missing an equals sign we want to error.
- The basic idea behind recursive-descent parsing is that in the entry point of `parseProgram` we construct the root node of the AST (in `newProgramASTNode()`), where we then build child nodes, and statements by calling other functions.
- The parser repeatedly advances the tokens and checks the current token to decide what to do next, either call another parsing function or error.

The first thing `ParseProgram` does is construct the root node of the AST and then it iterates over every token until it encounters an EOF token. We then write individual functions that handle each of the different kind of statements we get.

`parseLetStatement` constructs an `*ast.LetStatement` node and then advances the tokens while making assertions about the next token with calls to `expectPeek`.

`expectPeek` is an assertion method that almost all parsers share. Their primary purpose is to enforce the correctness of the order of tokens by checking the type of the next token. It then advances the tokens if the type is correct. If the type is not correct, we need to handle this error and show it to the user.

### Parsing expressions

Parsing statements (let and return) are both pretty easy. Expressions are a bit harder, for example, an expression like `5 * 5 + 10` needs to communicate operator precedence. Theres other stuff too meaning that the validity of a token's position now depends on the context, the tokens that come before and after, and their precedence.

In Monkey, everything besides `let` and `return` is an expression. These can be:

- prefix like `-5`, `!true` and `!false`
- Infix like `5 + 5`, `5 - 5`
- Comparison operators `foo == bar`, `foo != bar`, `foo < bar`
- Using parentheses to group like `5 * (5 + 5)`
- Call expressions like functions `add(2, 3)`
- Identifiers `foo * bar / foobar`

There's a bunch of things here, and we will start using what's called...

### Top Down Operator Precedence

A guy called Vaughan Pratt wrote a paper in 1973 that describes Top Down Operator Precedence Parsing, or Pratt parsing. TLDR: it describes parsing functions with single token types, and these token types can have two parsing functions which allows us to handle infix AND prefix token positions.

- **Prefix operators** go before `--5` an operand. The operator is `--` and the operand is the integer literal `5`.
- **Postfix operators** look like this `5++` where the operator is `++` and the operand is `5`. We won't have postfix operators in Monkey.
- **Infix operators** sit in between operands, like this `5 * 8`. These appare in binary expressions, which have two operands. This touches on something called operator precedence, or order of operations.

We need to add a new type of statement to the AST, an expression statement that looks like `x + 10;`.

### Implementing the Pratt Parser

A Pratt parser's main idea is the association of parsing cuntion with token types. Whenever this token type is encountered, the parsing functions are called to parse the appropriate expression and return an AST node that represents it.

`prefixParseFn` and `infixParseFn`. `prefix...` gets called when we encounter the associated token type in prefix position and `infix...` gets called when we encounter the token type in infix position.

We'll start with identifiers, which are simple and can look like `x;`, but also exist as arguments in function calls, operands in infix expressions and stand alone as part of conditionals.

Our `parse...Statements` follow the pattern of building the AST node and then trying to fill its fields by calling other parsing functions.

We can use the `iota` keyword to give the following constants incrementing numbers as values, starting at 0. The `_` blank identifier takes the zero value and the following constants get assigned values 1 to 7. The numbers don't matter, but the order and relation to the others do.

We've modified the `New` function to initalise the `prefixParseFns` map on Parser and register a parsing function so that if we encounter a token of type `token.IDENT` we call `parseIdentifier`.

### Integer Literals

Integer literals look like `5;` but are in a number of places, `let x = 5;` `add(5, 10)`

### Prefix Operators

Two prefix operators, `!` and `-`. Any expression can follow a prefix operator