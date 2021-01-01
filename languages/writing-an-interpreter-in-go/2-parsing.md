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

Parsing statements (let and return) are both pretty easy. Expressions are a bit harder, for example, an expression like `5 * 5 + 10` needs to communicate operator precedence

