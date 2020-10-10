# Common Programming Concepts

## Variables and Mutability

- Variables are immutable by default. This means if we try to reassign a variable without marking it as `mut`, we'll get a compiler error.
- You also have constants, which cannot be mutable. You also have to give the type too. You'd define a const like so: `const MAX_POINTS: u32 = 100_000;`

### Shadowing

- You can declare a variable with the same name as a previous variable.
- Shadowing is different from declaring a variable as `mut` because we'll get a compile-time error if we try to reassign to this variable without using `let`.
- Shadowing also allows us to change the type of the value as well. This is because we're essentially defining a brand new variable with the same name.

## Data Types

- The compiler can usually infer the type we're going to use. Sometimes when many types could be correct, we need to add a type annotation.
- Rust has classic *scalar* (single value) types like: integers, floating points, Booleans and chars.
- Rust also has a number of *compound* types.
  - *Tuples*: `let tup: (i32, f64, u8) = (500, 6.4, 1);`. You then get the values out by pattern matching to destructure it: `let (x, y, z) = tup;`. You could also get them by their index, `let five_hundred = x.0;`
  - *Arrays*: `let a = [1, 2, 3];`. Arrays store data in the stack instead of the heap. Arrays cannot grow in size, unlike a vector.

## Functions

- Rust uses snake_case for function and variable definitions.
- You need to give a parameter a type definition in function heads, `fn function(x: i32, y:i 32) {`
- For return values, we don't name them but we declare their type after an arrow. `fn five() -> i32 {}`
- When we want to return a value, we leave off the semicolon, so:

```rust
fn five() -> i32 {
    5
}
```
You can also say `return` too, but I'm not yet sure why one vs the other

## Control Flow

### `if` statements

- `if` expressions look like `if number < 5`.
- Rust won't do a JS and coerce anything to a boolean, you have to be explicit that it's a boolean.
- You can also use `if` in a `let` statement like a ternary: `let number = if condition { 5 } else { 6 };`

### Loops

- You can return a value from a loop like so:

```rust
let result = loop {
    break 1
}
```

Here, the value after `break` will be assigned to `result`.
- You've got conditional loops with `while`, `while number != 0`
- `for in` lets you loop over the elements of a collection:

```rust
fn main() {
    let a = [10, 20, 30];

    for element in a.iter() {
        println!(element);
    }
}
```

- People prefer to use `for` loops which you'd do by using a `Range` type like so:

```rust
fn main() {
    for number in (1..4).rev() {
        ...
    }
}
```
