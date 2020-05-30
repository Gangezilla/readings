// FIXME: Prevent this file from compiling! Diff budget: 1 line.
#[derive(Clone, Copy)]
struct MyType(1);

// Note: do not modify this function.
fn main() {
    let x = MyType(10);
    let y = x;
    let z = x;
}

// Since the main function requires a size of 10 to instantiate `MyType`, we can change that to a value less than 10 and it won't compile.