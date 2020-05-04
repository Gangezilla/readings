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

### Control

Having control over memory access, memory layout and specific CPU instructions is v important when optimising perf. For example, it might matter if data is stored in the stack rather than on the heap. You also sometimes will need to add reference counting to a shared value, or pass references to functions. For example, there's a bunch of ways that you can define a number:

- `let a = 10;` will store an integer on the stack
- `let b = Box::new(20);` will store an integer on the heap (also known as a box integer)
- `let c = Rc::new(Box::new(30));` is a boxed integer wrapped within a reference counter
- `let d = Arc::new(Mutex::new(40));` is an integer protected by a mutual exclusion lock wrapped in an atomic reference counter.

## Rust's Three Big Features

### Performance

For software to run faster, it needs to do less. Rust pushes this burden onto the compiler which aggressively optimises both the size and speed of your program. It also:

- Provides cache-friendly data structures by default. Arrays usually hold data within Rust programs rather than nested tree structures created by pointers. This is called data-oriented programming.
- Having a modern package manager makes it easier to bring in good deps.
- Methods are always dispatched statically unless dynamic dispatch is explicitly requested, which enables the compiler to optimise code sometimes eliminating it completely.

### Concurrency

Rust is very good at concurrency, with many people saying it has "fearless concurrency". It's emphasis on safety makes concurrency safe and easy.

### Memory efficiency

When needed you can use fixed-size structures and know exactly how every byte is managed.

## Downsides

- Hard to model cyclic data structures like graphs. Implementing a doubly linked list is hard because of Rust's safety checks
- Compile times
- Strictness, its very hard to be lazy when programming with Rust
- Size of the language: Rust is a very big language and it can be intimidating. The downside of allowing full control is that programmers have the burden of choice.

## Where does Rust fit best?

- Command line utilities. Rust programs are fast because they don't have an interpreter (Ruby or Python) or virtual machine (Java or C#).
- Data processing
- Extending an application, it enables "ruby gems in rust" which is pretty cool.
- Resource constrained environments such as microcontrollers.
- Server-side applications that would sit between the OS and the application like DBs, servers and search. For example the npm package registry is written in Rust.
- Desktop apps
- Mobile apps in the form of "native applications"
- Web in the form of WASM. You can port a Rust project to the browser with two additional commands on the command line.
- Systems programing like video game engines, compilers and operating systems.

## Notes from hello2

- Strings in Rust are able to include a wide range of characters. Strings are UTF-8 so you can use non-English characters and emoji with ease.
- The `!` is used to signal the use of a macro. A macro can be thought of as fancy functions for now. They offer the ability to avoid boilerplate code, and in the case of `println!` theres a bunch of type detection going on so that arbitrary data types can be printed.

## Garbage collection

A garbage collector is a service that tells the operating system that one of your variables has left scope and the memory allocated is able to be used by others. It's convenient but makes your program slower. Rust has no garbage collector but offers the convenience of one.

You may have noticed that we haven't added any type annotations to our example code. Rust is statically typed meaning the behaviour of all data is defined in advance of the program being run.
