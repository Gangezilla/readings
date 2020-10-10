# Getting Started

## Intro

- Run `rustup update` to update your installed version of rust to the latest version.
- The `main` function is special. It's always the first code that runs in every executable Rust program. `fn main()` defines a function called 'main' with no params and no return value.
- Rust style indents with four spaces, not a tab.
- `println!` calls a Rust macro, as denoted by the `!`
- `;` indicates a line is over.
- Before running a Rust program you've gotta compile it with `rustc`, which spits out an executable.

## Cargo

- `cargo new NAME` creates a new directory with a basic main file and a `Cargo.toml`, which looks like a `package.json`
- When we're going to build and run it we run `cargo build`, we can then run `cargo run` to execute it. We do this with cargo to bundle in dependencies and stuff.
- We can also use `cargo check` to make sure that everything is still valid and peachy which is a lot quicker than doing a whole new build.