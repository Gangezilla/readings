# Generic Types, Traits and Lifetimes

Generics are abstract stand-ins for concrete types or other properties. We can express the behaviour of generics or how they relate to other generics without knowing what will be in their place when compiling and running the code.

## Generics

### Removing Duplication by extracting a function

We're going to refactor this function:

```rust
fn main() {
    let number_list = vec![34, 50, 25, 100, 65];
    let mut largest = number_list[0];
    for number in number_list {
        if number > largest {
            largest = number;
        }
    }

    println!("The largest number is {}", largest);
}
```

If we want to find the largest in multiple arrays we can pull this function out, and lets also say we have another function to find the largest char.

```rust
fn largest_i32(list: &[i32]) -> &i32 {
    let mut largest = &list[0];

    for item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

fn largest_char(list: &[char]) -> &char {
    let mut largest = &list[0];

    for item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

fn main() {
    let number_list = vec![34, 50, 25, 100, 65];
    let result = largest(&number_list);
    println!("The largest number is {}", result);

    let char_list = vec!['y', 'm', 'a', 'q'];
    let result = largest_char(&char_list);
    println!("The largest char is {}", result);
}
```

We can use generics to further refactor this

```rust
fn largest<T>(list: &[T]) -> &T {
    let mut largest = list[0];

    for item in list {
        if item > largest {
            largest = item;
        }
    }

    largest
}

fn main() {
    let number_list = vec![34, 50, 25, 100, 65];
    let result = largest(&number_list);
    println!("The largest number is {}", result);

    let char_list = vec!['y', 'm', 'a', 'q'];
    let result = largest(&char_list);
    println!("The largest char is {}", result);
}
```

### In Structs

```rust
struct Point<T> {
    x: T,
    y: T,
}

fn main() {
    let integer = Point { x: 5, y: 10};
    let float = Point { x: 1.0, y: 4.0 };
}
```

Generics don't mean "anything", they have to be consistent. So in these examples we've used integers and then floats and its ok cos they're of the same type. If we tried to mix a float and an integer we'd get a compiler error. If we wanted this, we'd have to define our struct with multiple generic types:

```rust
struct Point<T, U> {
    x: T,
    y: U,
}
```

## Traits: Defining Shared Behaviour

A trait tells the Rust compiler about functionality a particular type has and can share with other types.

### Defining a Trait

A type's behaviour consists of the methods we call on that type. Diff types share the same behaviour if we can call the same methods on all of those types. Trait definitions are a way to group method signatures together to define a set of behaviours necessary to accomplish some purpose. We define and call a trait like so:

```rust
pub struct Tweet {
    pub username: String,
    pub content: String,
}

pub trait Summary {
    fn summarize(&self) -> String;
}

impl Summary for Tweet {
    fn summarize(&self) -> String {
        format!("{}: {}", self.username, self.content)
    }
}

fn main() {
    let tweet = Tweet {
        username: String::from("horse_ebooks"),
        content: String::from("of course, as you probably already know, people"),
    };

    println!("1 new tweet: {}", tweet.summarize());
}
```

...

## Validating References with Lifetimes

### Preventing Dangling References with Lifetimes

The main aim of lifetimes is to prevent dangling references, which cause a program to reference data other than the data its intended to reference. 