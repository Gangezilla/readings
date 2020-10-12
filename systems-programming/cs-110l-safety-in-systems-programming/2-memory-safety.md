# Memory Safety

- Double 'free' is bad because it corrupts heap state. It's also a security vulnerability.
- It's really hard to reason about programs, often impossible. The solution is in the language and the compiler. This is because you can start layering in constraints and then get some guarantees based on that.
- A lot of the guarantees we get from Rust come from the checks its compiler performs.

CS242 (programming languages)
CS143 (Compilers)

## How does Rust prevent these errors?

- Ownership
- Each value in Rust has a variable that's called its *owner*. Each resource in Rust, you can only have one owner at once. RAII, Resource Acquisition is Initialization is a big idea in Systems Programming.

Controlling references to resources is a broader idea in systems programming that isn't unique to Rust. We don't want our resources to hang around for longer than we need them, want to relinquish them when we don't need them.

- Integers implement a `Copy` trait, whereas `Strings` do not. There's a special subroutine that when an equals sign is seen for integers, it gets copied instead of moved/transfer of ownership.
- A lifetime of a value starts when it's created and ends the last time it's used. Rust doesn't let you have a reference to a value that lasts longer than the value's lifetime.
- Rust calls the `drop` function on a value once its lifetime ends.
- We use the `&` to borrow stuff.
- Ownership and borrowing is enforced at compile time. This is essentially making a fixed cost investment in our preprocessing. It's generally desirable to shift checks from runtime to compile time.

Rust is an *expression based language*. In most languages there are *expressions* which evaluate to values and *statements* which do not. In Rust, everything is an expression. Functions are sequences of expressions separated by semicolons, evaluating to the value of the last expression. This is why you don't include a semicolon at the end of a function. If you wrote something like this:

```rust
fn sum(a: i32, b: i32) -> i32 {
    a + b;
}
```

You'd get an error! This is because this function consists of two expressions; `a+b` and then an empty expression after the semicolon. You'll get an error because the return value is void, but you've specified that it should be `i32`.