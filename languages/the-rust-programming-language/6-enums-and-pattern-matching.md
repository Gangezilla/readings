# Enums and Pattern Matching

## Enums

We define an enum like this:

```rust
enum IpAddrKind {
    V4,
    V6,
}
```

We can create instances of each of these variants like so:

```rust
let four = IpAddrKind::V4;
let six = IpAddrKind::v6;
```

We can then define a function that takes any `IpAddrKind`

```rust
fn route(ip_kind: IpAddrKind) {}
```

If we wanted to go further and store an IP address, we can combine an enum with a struct

```rust
enum IpAddrKind {
    V4,
    V6,
}

struct IpAddr {
    kind: IpAddrKing,
    address: String,
}
```

We could do this more concisely too

```rust
enum IpAddr {
    V4(String),
    V6(String),
}

let home = IpAddr::V4(String::from("127.0.0.1"));
```

## The `Option` Enum

The `Option` type is an enum defined by the standard library and its used in many places where a value could be something or nothing. Using the type system for this means the compiler can check that you've handled everything you should be handling.

Rust does not have a `null` value. With null values the concept its trying to epxress is that a value can be invalid or absent. Rust uses an enum that can encode the concept of a value being present or absent, which is `Option<T>`

```rust
let some_number = Some(5);
let some_string = Some("a string");

let absent_number: Option<i32> = None;
```

## The `match` Control Flow Operator

`match` is very expressive, and the compiler will confirm that all possible cases are handled. `match` is powerful and different to an `if` statement because `if` requires a Boolean result, whereas match can be anything.

```rust
enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter,
}

fn value_in_cents(coin: Coin) -> u8 {
    match coin {
        Coin::Penny => 1,
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter => 25,
    }
}
```

A `match` statement is made up of "arms", which is a pattern and some code. You can also use `_` as a default value.

## Concise Control Flow with `if let`

```rust
if let Some(3) = some_u8_value {
    println!("three!");
}
```

This lets us easily handle valus that match one pattern while ignoring the rest. This is good if you don't care about most of the values.