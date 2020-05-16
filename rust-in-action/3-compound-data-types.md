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
