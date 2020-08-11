# Lexing

## Lexical Analysis

In order for us to work with source code we need to make it more accessible. The first step then becomes representing our source code in an easier to work with format. It then looks like this:
**Source code -> Tokens -> AST**
The transform from source to tokens is called lexical analysis/lexing. It's done by a lexer/tokenizer/scanner. Tokens are small, easily categorisable data structures that are then fed to the parser which does a second transform and turns the tokens into an AST.

If we had code like `let x = 5 + 5;` this would look like:

```monkey
[
  LET,
  IDENTIFIER("x"),
  EQUAL_SIGN,
  INTEGER(5),
  PLUS_SIGN,
  INTEGER(5),
  SEMICOLON
]
```

Here we don't care about whitespace. If this was Python, we'd have to keep track of that. In prod, we might have the line number, column number and filename associated with a token so we could make better errors.

## Defining our tokens

The snippet we're going to focus on looks like this:

```monkey
let five = 5;
let ten = 10;

let add = fn(x, y) {
  x + y;
};

let result = add(five, ten);
```

- We save the numbers as integers
- We save the variables as "identifiers"
- We call the other words that form part of the language "keywords"
- We've also got special characters, that we need to store separately cos a ( is different from a }

## The Lexer

Our lexer will take source code as input and output the tokens that represent the source code. We'll make our life simpler by just taking in the file as one big string. In prod, we'd probably want to use `io.Reader` so we can know filename and lines etc but not here.
