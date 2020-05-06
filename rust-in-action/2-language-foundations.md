# Language Foundations

- Building `grep-lite`, should be able to grok most Rust programs after this.

## A glance at rust's syntax

Rust tries to be boring and predictable with variables, numbers functions etc. Blocks are delimited by `{}` and uses a single equals sign for assignment `=`. This is a simple program:

```rust
fn main() { // you can put main wherever you want
    let a = 10; // types can be inferred from the compiler
    let b: i32 = 20; // or declared by the programmer when creating variables
    let c = 30i32; // numeric types can include a type annotation in their literal form
    let d = 30_i32; // underscores increase readability
    let e = add(add(a, b), add(c, d));
    println!(e);

    fn add(i: i32, j: i32) -> i32 { // type declarations are required when defining functions
        i + j // functions return the last expressions result, meaning return is not required. BUT be careful as adding a semicolon would change the semantics to return () instead of i32
    }
}
```

Let's break it down

- `fn main() {`
  - `fn` keyword begins a function definition
  - `main()` is the entry point and can appear anywhere in the file. It takes no args, and returns no value.
  - Code blocks also known as lexical scopes are defined with braces `{}`
- `let a = 10;`
  - use `let` to declare variable bindings. Variables are immutable meaning they're read-only rather than read/write.
  - Statements are delimited with semi-colons `;`
- `let b: i32 = 20;`
  - You can designate a specific data type to the compiler. Sometimes the compiler can't figure it out
- `let c = 30i32;`
  - Rust's numeric literals can include type annotations which can be helpful which can he helpful with complex numerical expressions.
- `let c = 30_i32;`
  - Same as above, but with an underscore to make it more readable
- `let e = add(add(a, b), add(c, d));`
  - Calling functions is the same as other languages
- `println!()`
  - `println!` is a macro. Macros are function-like but return code rather than a value. In printing, every data type has its own way of being converted to a string. `println!` takes care of figuring out the exact methods to call on its arguments.
  - Strings use double quotes `"` rather than single quotes.
  - Sting formatting uses `{}` as a placeholder rather than `%s`
- `fn add() -> i32 {}`
  - Rust's syntax for defining functions is pretty familiar. Commas delimit parameters, type declarations follow variable names. The "thin arrow" syntax indicates return type.

You can compile a single file into an executable using rustc like `rustc first-steps.rs` and then execute it like you would a normal unix executable.

### Starting out with numbers

- `let floats = 21.0`
  - Floats work just as you'd expect, no need for special syntax
- `let one_million = 1_000_000` underscores can be used to increase readability
- `let three = 0b11;` you can incidate base 2 binary numbers with `0b`
- `let thirty = 0o36;` you can do base 8 octal numbers with `0o`
- `let three_hundred = 0x12C` you can do base 16 hex numbers with `0x`

Types:
`i8`, `i16`, `i32`, `i64`: signed integers
`u8`, `u16`, `u32`, `u64`: unsigned integers
`f32`, `f64`: floating point numbers in 32bit and 64 bit variants
`isize`, `usize`: integers that assume CPU's "native" width (ie a 64 bit system will be make these 64 bits wide)

You can represent the same number with different types to save memory
20 -> u32 -> 00000000000000000000000000010100 in memory
20 -> i8 -> 0010100 in memory
