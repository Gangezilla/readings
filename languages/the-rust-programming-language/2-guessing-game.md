# Guessing Game

- `use std::io;` brings in the `std::io` package.
- `let` is used to create a variable, and `mut` is used to make a variable mutable.
- `String:new` is a function that returns a new instance of String. `String` is a string type that is a growable, UTF-8 encoded bit of text.
- `::` syntax indicates that new is an *associated function* of the `String` type. An associated function is implemented on a type, rather than on a particular instance of a `String`.
- `.read_line` calls the `read_line` method and takes an `&mut guess` argument. The `&` is a reference, not a pointer. References are immutable by default, and so we say `mut` to let Rust know we plan on mutating that value.
- The `.expect()` when we read a line is to help us deal with failure with the `Result` type.
  - Rust has a number of `Result` types in its standard library which are enums. For `Result`, the variants are `Ok` or `Err`. `Ok` indicates the operation was successful, and `Err` indicates it failed. An instance of `Result` has an `expect` method which gets executed if the operation fails.
- Values get printed in `println` like `println!("something {}", variable)` by using the curly brackets.
- Cargo ensures you get reproducible builds using the `Cargo.lock` file.
- `cargo update` will bump all the versions to safe versions.
- `Ordering` is another enum with the variants being `Less` `Greater` and `Equal`.
- We use a `match` expression, which is made up of *arms*. An arm consists of a pattern and the code that should be run if the value given at the start of the `match` fits the arm's pattern.
- If we define another variable with the same name, Rust lets us *shadow* the previous value with a new one. It's used when we want to have the same variable but of a different type, and saves us defining a different variable. 
- The `loop` keyword creates an infinite loop.
- We can then replace our error in parsing with a `match` statement to catch the error instead of crashing