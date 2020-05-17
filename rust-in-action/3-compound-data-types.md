# Compound Data Types

You've got some ways you can tell the compiler to relax while you're playing around.

- `#![allow(unused_variables)]` to allow unused variables
- `#[allow(dead_code)]`
- You can use `!` as a return type to tell Rust that the function never returns
- `unimplemented!()` will crash the program if its encountered.

## Modeling files with `struct`

`struct` lets us make a composite type that is made up of other types. Let's make one for a `File` type.

```rust
#![allow(unused_variables)]

#[derive(Debug)] // lets `println!` print File
struct File {
    name: String,
    data: Vec<u8>, // using vec lets us have access to dynamic sizing to we can simulate writing to a file
}

fn open(f: &mut File) -> bool {
    true
}

fn close(f: &mut File) -> bool {
    true
}

fn read(f: &File, save_to: &mut Vec<u8>) -> usize { // return number of bytes read
    let mut tmp = f.data.clone(); // make a copy of data, as save_to.append() will shrink the input Vec<T>
    let read_length = tmp.len();
    save_to.reserve(read_length); // ensures there is sufficient space to fit the incoming data, minimises allocations when inserting data byte by byte.
    save_to.append(&mut tmp); // allocate sufficient data in the save_to buffer to hold the contents of f
    read_length
}

fn main() {
    let f1 = File {
        name: String::from("f1.txt"), // String::from allows owned strings to be generated from string literals (which are slices)
        data: Vec::new(),
    }

    let f1_name = &f1.name;
    let f1_length = &f1.data_len(); // accessing fields by reference with the dot operator prevents use after move issues
}
```

## Adding methods to a `struct` with `impl`

Methods are functions that are coupled to an object. With them in Rust you don't need to specify one of the argumens. Instead of saying like `read(f, buffer)` you can go `f.read(buffer)`. To define methods we use `impl` blocks. A `struct` and `impl` go together like `Class` in other languages.

Objects can be instantiated with a `new()` method or literal syntax, but its easier to do it with `new`. `new()` isn't a language feature, but its a community convention, so you've gotta add `new` to `impl`.

You can also add in different helper functions to make this easier, like `new_with_data`

```rust
// literal
File {
    name: String::from("f1.txt"),
    data: Vec::new(),
};

// new
File::new("f1.txt", vec![]);

struct File {
    name: String,
    data: Vec<u8>,
}

impl File {
    fn new(name: &str) -> File {
        File {
            name: String::from(name),
            data: Vec::new(),
        }
    }

    fn new_with_data(name: &str, data: &Vec<u8>) -> File {
        let mut f = File::new(name);
        f.data = data.clone();
        f
    }
}
```

## Returning errors

### Modifying a known global variable

If you see the keyword `unsafe` in Rust it's a warning sign rather than an indicator. Unsafe in Rust means "the same level of safety offered by C at all times". This is a little program that uses global variables to propagate error info through a program

```rust
extern crate rand; // make crate available to our code
use rand; // bring rand into local scope

static mut ERROR: isize = 0; // init ERROR to 0

struct File; // creates a "unit type" with no fields to stand in for a real struct while we're experimenting

#[allow(unused_variables)]
fn read(f: &File, save_to: Vec<u8>) -> usize {
    // read from disk
    if rand::thread_rng().gen_weighted_bool(10_000) { //returns true 1/10000 times
        unsafe {
            ERROR = 1; // sets error to 1, notifys the rest of the system about an error
        }
    }

    0 // always read() 0 bytes
}

#[allow(unused_mut)]
fn main() {
    let mut f = File;
    let mut buffer = vec![];

    read(&f, buffer);
    unsafe { // accessing static mut's is unsafe
        if ERROR != 0 {
            panic!("An error has occured!")
        }
    }
}
```

This sort of style isn't used in Rust often. It's important to know tho cos sometimes systems programmers need to interact with system-defined global values, and software that interacts with CPU registers will need to get used to inspecting flags to check what operations were completed successfully.

## Making use of the `Result` return type

Rust's approach is to use a type that stands for both the standard case and error case, called a `Result`, which can be `Ok` or `Err`. We'd generally wrap the return value in `Ok(value)` if it goes well, or `Err(E)` if not. If `Err(E)` is returned, the whole program panics and shuts down.

Using `Result` provides you with compiler-assisted code correctness as your code won't compile unless you've taken the time to handle edge cases.

## Defining and making use of enum

An enum is a type that can represent multiple known variants, often like several pre-defined known options like playing cards.

```rust
enum Suit {
    Clubs,
    Spades,
    Diamonds,
    Hearts,
}
```

Enums are useful because they give the compiler some knowledge of what an expected value or edge case might look like.

```rust
#[derive(Debug)] // let enum be printed to screen
enum Event {
    Update,
    Delete,
    Unknown,
}

type Message = String;

fn parse_log(line: &'static str) -> (Event, Message) {
    let parts: Vec<&str> = line.splitn(2, ' ').collect(); // collect consumes the iterator from line.splitn and returns a Vec<T>
    if parts.len() == 1 {
        return (Event::Unknown, String::from(line))
    }

    let event = parts[0];
    let rest = String::from(parts[1]);

    match event {
        "UPDATE" | "update" => (Event::Update, rest),
        "DELETE" | "delete" => (Event::Delete, rest), // return structured data on a known event
        _ => (Event::Unknown, String::from(line)) // return the whole line when unrecognised
    }
}

fn main() {
    let log = "BEGIN Transaction XK342
UPDATE 234:LS/32231 {\"price\": 31.00} -> {\"price\": 40.00}
DELETE 342:LO/22111";

    for line in log.lines() {
        let parse_result = parse_log(line);
        println!("{:?}", parse_result);
    }
}
```

Enums:

- work nicely with Rust's `match` functionality
- support `impl` blocks

### Using enums to manage internal state

For example, we could use an enum to model the `FileState` of our previous `File` struct:

```rust
enum FileState {
    Open,
    Closed,
}

struct File {
    name: String,
    data: Vec<u8>,
    state: FileState,
}

fn open(mut f: File) -> Result<File, String> {
    f.state = FileState::Open;
    Ok(f)
}

fn close(mut f: File) -> Result<File, String> {
    f.state = FileState::Closed;
    Ok(f)
}
```

## Defining common behaviour with traits

Let's extend our `File` struct with traits. Regardless of where a file is (hard drive, cache, network...) we can define rules that say "To call yourself a file, you must implement _this_"

### Creating a read trait

Traits let the compiler know (and people!) know that multiple types are attempting to perform the same task. So the macros we saw earlier are traits and we can look at them and understand what they're going to do. Same with if we added a `Read` trait

```rust
struct File;

trait Read {
    fn read(self: &Self, save_to: &mut Vec<u8>) -> Result<usize, String> // a trait block includes the type signatures of functions that implementors must comply with.
}

impl Read for File {
    fn read(self: &File, save_to: &mut Vec<u8>) -> Result<usize, String> {
        Ok(0)
    }
}
```
