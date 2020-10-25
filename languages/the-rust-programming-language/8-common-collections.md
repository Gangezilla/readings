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

## Hash Maps

The type `HashMap<K, V>` stores a mapping of keys of type `K` to values of type `V` which it does via a hashing function.

### Creating a new Hash Map

```rust
use std::collections::HashMap;

let mut scores = HashMap::new();

scores.insert(String::from("Blue"), 10);
```

Hash maps store their data on the heap. You can also iterate over a vector of tuples with the `collect` method.

```rust
use std::collections::HashMap;

let teams = vec![String::from("Blue") String::from("Yellow")];
let initial_scores = vec![10, 50];

let mut scores: HashMap<_, _> =
    teams.into_iter().zip(initial_scores.into_iter()).collect();
```

We use the type annotation `HashMap<_, _>` because you can `collect` into many different data structures, and we use underscores because Rust can infer the types.

### Hash Maps and Ownership

For types that implement the `Copy` trait like `i32`, the values are copied into the hash map. For owned values like `String`, the values will be moved and the hash map will be the owner of those values

```rust
use std::collections::HashMap;

let field_name = String::from("Fave color");
let field_value = String::from("Blue");

let mut map = HashMap::new();
map.insert(field_name, field_value);

// here, field_name and field_value are invalid cos they're owned by map.
```

### Accessing Values in a Hash Map

We use the `get` method with the key we're after:

```rust
let mut scores = HashMap::new();

let blue = String::from("Blue");

scores.insert(blue, 10);

let score = scores.get(&blue);
```

We can loop over each k/v pair like so:

```rust
let mut scores = HashMap::new();

scores.insert(String::from("blue", 10));

for (key, value) in &scores {
    println!("{}: {}", key, value);
}
```

### Updating a Hash Map

#### Overwriting a Value

```rust
scores.insert(String::from("Blue"), 10);
scores.insert(String::from("Blue"), 25);
```

will give us 25

#### Only inserting if the key has no value

```rust
scores.insert(String::from("Blue"), 10);
scores.entry(String::from("Blue")).or_insert(50);
```

#### Updating a value based on the old value

```rust
let mut map = HashMap::new();

for word in text.split_whitespace() {
    let count = map.entry(word).or_insert(0);
    *count += 1;
}
```

Because `or_insert` returns a mutable reference to the value for this key, we can store it in a variable and then increment it.
