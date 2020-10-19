# Common Collections

There's a few collections in Rust:

- `vector`
- `string`
- `hash map`

## Vectors

`Vec<T>` or vectors allow you to store more than one value in a single data structure in a contiguous block of memory. We create a new vector like this:

```rust
let v: Vec<i32> = Vec::new();
```

It's more common to initalise a vector with values, and Rust gives us the `vec!` macro to do that:

```rust
let v = vec![1, 2, 3];
```

You can add to a vector like this: `v.push(8);`

When a vector goes out of scope, its freed just like any other struct. This includes dropping all of it's values.

### Reading Elements of Vectors

You can access vector values in two ways:

```rust
let v = vec![1, 2, 3, 4, 5];

let third: &i32 = &v[2];

match v.get(2) {
    Some(third) => println!("The 3rd element is {}", third),
    None => println!("There's no third element"),
}
```

We can iterate over the values in a vector like

```rust
for i in &v {
    println!("{}", i);
}
```

We can also iterate over mutable references to each element to make changes to each element:

```rust
let mut = vec![100, 32, 57];
for i in &mut v {
    *i += 50;
}
```

## Strings

It's useful to discuss strings in the context of collections cos strings are implemented as a series of bytes

### What is a String

Rust has a string type in the core language, `str`, and it's usually seen in it's borrowed form `&str`.

### Creating a new String

Many of the same functions we have with Vectors are available here too. We create a new string:

`let mut s = String::new();`

When we have some initial data we want to put into the string, we need to use the `to_string` method.

`let data = "initial stuff".to_string();`

or we can go like:

`let s = String::from("initial stuff");`

We can append to a string like this:

```rust
let mut s = String::from("foo");
s.push_str("bar");
```