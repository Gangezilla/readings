// FIXME: Make me compile! Diff budget: 1 line.

#[derive(Copy, Clone)]
struct MyType(usize);

// Do not modify this function.
pub fn main() {
    let x = MyType(1);
    let y = &x; // immutable reference to MyType
    let _z = *y;
}

// The function makes an immutable reference to `MyType` and then dereferences it. This isn't possible because y doesn't own the reference.
// We can make `MyType` copyable so that `let z = *y` can copy the value without requiring y be mutable.
