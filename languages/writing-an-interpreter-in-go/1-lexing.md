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

There's a limited number of token types, so we can define them all as constants.
## The Lexer

Our lexer will take source code as input and output the tokens that represent the source code. We'll make our life simpler by just taking in the file as one big string. In prod, we'd probably want to use `io.Reader` so we can know filename and lines etc but not here.

When we're writing the code, we need to be able to look ahead to see what comes next. This is so we can know if we're in any multi-char word like `fn` or whatever.

`readChar` gives us the next character and advances our position in the input string. We only use ASCII cos it's easier. If we wanted to support unicode, we would need to change `ch` to a `rune` and change how we read characters as they could be multiple bytes wide now.

Our lexer needs to recognise if the current character is a letter and if so, it needs to read the rest of the identifier/keyword until it encounters a non-letter-character and then identify if its an identifier or a keyword.

Monkey's number parsing is quite simple; we only support integers. No floats, no hex, no octal.

## Extending our token set and lexer

The new tokens we'll be adding (==, !, !=, -, /, *, <, > and the keywords true, false, if, else and return) will need to be classified as either:

- a one character token
- a two character token
- keyword token

Some of the code in the tests looks like nonsense which is ok. The lexer's job is not to tell us if code works or make sense, it only needs to turn input into tokens.

To handle `==` and `!=` we can extend our branches that look for the `=` and `!` chars and "peek" forward in the input we've been given.