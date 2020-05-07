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

Rust has pointers like C and Go. `*` is the dereference operator which "follows the reference and returns its referent". Or as I like to say "gets the value of the pointer". We can use it like this:

```rust
fn main() {
    let needle = 42;
    let haystack = [1, 1, 2, 5, 14, 42] // array literal for list of integers

    for reference in haystack.iter() { // .iter() returns an iterator over haystack that provides references to enabling access to individual elements
        let item = *reference; // item is the value referred to by reference
        if item == needle {
            println!("{}", item)
        }

        if reference == &needle { // alternate to above
        // reference == &needle converts needle to a reference and comapres against that
            println!("{}", reference)
        }
    }
}
```

### Type-aware control flow with match

Rust has a `match` keyword which is kinda like a switch statement. It's not quite as nice as Elixir's pattern matching but it's ok. Rust is good tho, cos it ensures you're testing against all possible values. You'd use it like this:

```rust
fn main() {
    let haystack = [1, 1, 2, 3, 5, 14, 42]

    for reference in haystack.iter() {
        let item = *reference

        let result = match item {
            42 | 132 => "hit!",
            _ => "miss"
        }

        if result == "hit!" {
            println("{}: {}", item, result);
        }
    }
}
```

`match` is important in Rust with many control sturctures being defined in terms of `match` under the hood.

### Getting stuff done with functions

One of the fundamental abstractions provided by programming languages is the subroutine and in Rust these are called functions

A function signature looks like this: `fn add(i: i32, j: i32) -> i32 {`. As you can see Rust requires us to define our parameters' types and the function's return type.

Let's break it down.

- `fn`: keyword
- `add`: identifier
- `i`, `j`: parameters
- `i32`: type
- `->`: thin arrow to indicate return
- `i32`: return type
- `{`: beginning of code block

#### Advanced function definitions

Rust's functions can get pretty gnarly, so let's look at a few.

##### Explicit lifetime annotations

`add_with_lifetimes<'a, 'b>(i: &'a i32, j: &'b i32) -> i32`

TL;DR: the extra info is giving more specific info to the Rust compiler about data that lives outside the function. Functions that use references - denoted by the ampersands preceding the types - have data that exists outside of their scope.

Objects that live outside of a function are checked to make sure that accessing them is valid throughout that function. Rust checks to ake sure that all input data will live at least as long as the function that needs it.

Underpinning Rust's safety checks is a **lifetime** system that tends to be able to work unaided. Usually, lifetime parameters don't need to be provided which is known as lifetime elision. The names `'a` and `'b` are arbitrary.

`i: &'a i32` reads as "variable i is a reference to a 32 bit integer with lifetime 'a'".

#### Generic Functions
