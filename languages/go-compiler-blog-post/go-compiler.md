
`go tool compile -W`

`go tool compile -m` flag shows you compiler optimisations. where is this in the code?

`go tool compile -S` shows you what it looks like in assembly language.



## How does code get compiled?

So we have interpreted and compiled languages, brief explainer of the difference. Classic difference is that compilers generate native machine code, and interpreters read source code and generate machine code on the fly.
Go is a compiled language which gives us some advantages, such as error checking, fast performance and the compiler doing optimisations of our code.
But what's actually happening under the hood when you run `go build`.

"""
The compiler does the following
- initalises some common data structures
- iterates through all of the provided Go files and parses them
- parsed in `compile/internal/syntax/scanner.go`.
- You can take a look at `compile/internal/syntax/tokens.go` as well to see all the valid tokens in Go.
- This is more formally defined here [https://golang.org/ref/spec] if you feel like some light bedtime reading.
- After parsing, a complete parse tree is created where each node represents an element of the compiled program.
- Recursively iterates through the generated tree several times and applies some modifications
- Performs the actual compilation after the parse tree is complete.
- Creates the object file that contains generated assembly code with some additional data structures

"""

- `asm/internal/lex/tokenizer.go/Next()` => `text/scanner.go/Scan()`
- `internal/syntax/scanner.go`, `internal/syntax/tokens.go`, `token_string.go`, `source.go`

- Phases of compiler (according to some website... https://www.guru99.com/compiler-design-phases-of-compiler.html)
  - lexical analysis
  - syntax analysis
  - semantic analysis
  - intermediate code generation
  - code optimisation
  - code generation

- Lexer generates an AST. Step through the code of `scanner.go` a bit, pretty neat that you can see what happens for every single thing. The primary function here is `Scan()`, talk about this and generate an AST with go. Post your source code and what the tree looks like.
- Compiler takes the AST and spits out machine code, do that and explain whats happening. pointing to the relevant source code where it occurs.

Ideally I'd love to be able to point to the primary files and functions where the path of `go build` runs through.


## The design of the Go Assembler - Rob Pike 2016

- Assembler is how you talk to the machine at the lowest level.
- We used to only have assembler, and higher level languages like COBOL displaced it.
- We still need it sometimes for environment bootstrap, low-level lib code, performance and access to features not exposted in language.
- Assembly language is how people think about the computer. Worth understanding a bit to know how the computer works.
- CPUs being pretty similar allow us to have a common grammar.
- Assembler is a way to hand write the pseudo instructions the compiler is generating.
- Go 1.3 they wanted to get rid of all the C and start moving everything to Go.
- As of Go 1.3, more traditional linker. the obj library has been moved to the backend of the compiler and the assembler that feed into the linker. The Go assembler is weird, takes in textual pseudo instructions and makes instructions.
- `go tool compile` you configure it with `GOOS` pronounced goose and `GOARCH` pronounced as gorch.
- `go tool link`
- `go tool asm`, goal was to write one tool. Not universal

```golang
package add

func add(a, b int) int {
  return a + b
}
```

- common grammer, they all look the same. instructions have diff names, word size differs, registers differ.
- Common input language so we can write an assembler.
- Downside of looking at Go's assembler to an outsider is it looks really odd because it doesn't use the same assembly notation as others.
- Go 1.5 assembler, common lexer and parser across all architectures. Each instruction parsed into an instruction description.
- Assembler just does text processing, has no clue on syntax.
- New assembler was tested against the old (C-written) ones. Tested the old output vs the new output and tweaked it.
- To a large extent, the assembler is now table-driven
- Assembly language really is the same everywhere and we should treat it that way. This lets us build a true common assembly language.

ideas?

compiler, linker, assembler?

where does an interpreter sit in here?