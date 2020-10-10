# Structs

To define a struct, we enter the keyword `struct` and name it.

```rust
struct User {
    username: String,
    sign_in_count: u64;
}
```

To use a struct after we've defined it, we create an instance of it by specifying concrete values for each of the fields.

```rust
let user1 = User {
    email: String::from("blah@blah.com")
    sign_in_count: 1,
};
```

We can't make individual struct fields mutable, the whole struct must be.

You can also use object key shorthand like JS

```rust
let email = "blah@blah.com";

let user1 = User {
    email,
    sign_in_count: 1,
};

```

## Using Tuple Structs without named fields to create different types

You can also define structs that look like tuples, called *tuple structs*.

```rust
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

let black = Color(0, 0, 0);
let origin = Point(0, 0, 0);
```

## Methods

You can also put methods on structs.

```rust
struct Rectangle {
    width: u32,
    height: u32,
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
}
```

If we wanted to change a value in a struct, we'd need to have `&mut self` as the first param.