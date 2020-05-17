// Basics

// Functions
fn add(x: i32, y:i32) -> i32 {
    x + y
    // implicit return (no semi)
    // explicit return `return x + y`
}

// Main function
fn main() {
    // Numbers
    // immutable bindings
    let x: i32 = 1;
    // x = 3; <-- compile time error

    // mutable variable
    let mut mutable = 1;
    mutable = 4;
    mutable += 2;

    // integer/float suffixes
    let y: i32 = i3i32;
    let f: f64 = 1.3f64

    // Type inference
    // Rust can figure out types most of the time
    // But its nice to be explicit

    let implic_x = 1;
    let implicit_f = 1.3;

    // Arithmetic
    let sum = x + y + 13;

    // Strings
    // String literals
    let x: &str = "hello world!";

    // Printing
    println!("{}, {}", f, x);

    // A 'String' - a heap allocated string
    let s: String = "hello world".into();
    let s2: String = "hello world".to_string();
    let s3: String = String::from("hello world");

    // a string slice is an immutable view into another string
    // its essentially a pair of pointers to a start and end of a string buffer
    let s_slice: &str = &s;
    let s_slice2: &str = &s[6..11];
    let s_slice3: &str = &s[6..];
    let s_slice4: &str = &str[..5];
    println!("{} {}", s, s_slice); // hello world hello world

    // Vectors/arrays

    // a fixed size array
    let four_ints: [i32; 4] = [1, 2, 3, 4];

    // a dynamic array (vector)
    let mut vector: Vec<i32> = vec![1, 2, 3, 4];
    vector.push(5);

    // mutability is inherited by the bound value.
    // if 'vector' is not declared 'mut' then the value can't be mutated
    let vector: Vec<i32> = vec![1, 2, 3, 4, 5];
    // vector.push(5); <-- compile time error

    // a slice - an immutable view into a vector or array
    let slice: &[i32] = &vector;
    let slice2: &[i32] = &vector[1..4];

    // use '{:?}' to print something debug style
}