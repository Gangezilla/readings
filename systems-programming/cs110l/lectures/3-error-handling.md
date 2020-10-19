# Error Handling

## Ownership in C

Example of some C code where it returns an error string in `*errp`, and the caller is responsible for `free`ing this memory. This is an example of ownership in C, where the caller is now responsible for this.

## Compile time vs run time

Rust makes you fix problems at compile time even though it feels a bit annoying at the time. At compile time, Rust is v different to C. At runtime it's pretty much the same. When you pass ownership in Rust it's like passing a pointer in C. No performance difference between ownership and passing a reference around.

Rust's model is you can have one person modifying and nobody else doing anything with a variable, or lots of people can view it.

## Error handling

Rust handles errors very differently to C and C++ code.

## Handling nulls

Nulls are so dangerous because they point to an invalid place in memory and will cause a segfault if we try to access it. There's significant consequences for misusing a null.

Nulls are so problematic because they place a huge burden on the programmer to keep track of what can and can't be null.

Rust solves this issue by introducing a type called `Option` that can have a value of `Some` or `None`. This indicates that this value could be null, and the compiler encourages you to handle it. You can do it with an `if` statement or the `match` statement.