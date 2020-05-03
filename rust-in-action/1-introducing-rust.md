# Introducing Rust

- `#!` Also known as "hash bang" syntax signifies that the attribute refers to whatever is in the current scope of the attribute.
- `extern crate chrono;` imports an external crate.
- `#[macro_use]` This brings macros from an external crate into local scope. The `#` signifies that the attribute refers to the item that immediately follows the attribute like so:

```rust
#[macro_use]
extern crate rocket;
```

- `use chrono::prelude::*;` Brings all exported members of `chono::prelude` into local scope.
- `use rocket::response::content::Html;` in contrast to the above, only import in the `Html` type
- Delcaring a struct:

```rust
struct Timestamp {
    t: String,
}
```

- `fn index() -> Html<String> {}` define a function called index that returns a Html that wraps a string.
- Rust distinguishes between `str` and `String`. `String` has more features, `str` is lightweight.
- `()` is a blank type called "unit", and its returned by expressions when there is no other meaningful return value.

Rust has three concurrent releases: stable, beta and nightly.

- Stable is updated every 6 weeks, and promises always available features that are always backwards compatible.
- Beta is primarily use by CI systems, few humans use it.
- Nightly version is where new language features are incubated. Doesn't imply unsafe Rust, implies you're willing to accept changes in the future.

Many of Rust's features are drawn from two programming sub-fields:

- Systems programming: Rust draws the notion of control and a willingness to strip back abstraction when required.
- Functional programming: Rust provides efficient implementations of higher-order programming, an impressive type system, pattern matching and first class support for generics.

## What is Rust?

Rust's distinguishing feature (as a programming language) is its ability to prevent invalid data access at compile time. It guarantees that your program is memory safe without imposing any run time costs (FYI: Memory safety is the state of being protected from various software bugs and security vulnerabilities when dealing with memory access).
Rust's distinguishing feature (as a professional community) is the willingness to explicitly include values into its decision making process. It's compiler errors are great, the community is helpful, and the messaging around the language puts people first.

Rust has three goals: safety, productivity and control.

### Safety

Rust programs are free from:

- dangling pointers, live references to data that becomes invalid over the course of the program.
- data races, which is an inability to determine how a program will behave from run to run because external factors are changing.
- buffer overflow, which is attempting to access the 12th element of an array of only 6 elements.
- iterator invalidation, an issue caused by something that is being iterated over being altered mid-way through

### Productivity

When given a choice, Rust prefers the option that is easiest for the developer.
It also has many ergonomic features. It offers generics, sophisticated data types, pattern matching and closures.
