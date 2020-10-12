# Ownership

## What is Ownership?

Ownership is Rust's central feature.

All programs have to manage the way they use a computer's memory while running. Some languages have garbage collection that looks for no longer used memory as the program runs, in other languages the programmer must explicitly manage memory. Rust uses a third approach, where memory is managed through a system of ownership with a set of rules that the compiler checks at compile time.

### The Stack and the Heap

The staack an the heap are parts of memory that are available to your code to use at runtime but they're structured in different ways. The stack stores values in the order it gets them and removes them in the opposite order. This is referred to as *last in, first out*. Adding data is called pushing onto the stack, and removing data is called popping off the stack.

All data on the stack must have a fixed, known size. Data with an unknwon size at compile time, or a size that you might change must be stored on the heap. The heap is less organised, when you put data on it, you request a certain amount of space and the memory allocator find room and gives you a pointer to it.

Pushing to the stack is faster than allocating on the heap because the allocator never has to search for a place to store new data cos the location is always on the top of the stack.

Accessing data in the heap is slower than accessing data on the stack because you have to follow a pointer to get there.

## Ownership Rules

- Each value in Rust has a variable that is called its *owner*.
- There can only be one owner at a time.
- When the owner goes out of scope, the value will be dropped.

## Variable Scope

A scope is the range within a program for which an item is valid. The variable is valid from the point at which its declared until the end of the current scope.

## The `String` Type

We're gonna use `String` as an example because it's stored on the heap. Rust has string literals which we used earlier, but also a `String` type. The `String` type is useful for when we need to create a string during the running of a program, like taking user input. This is allocated on the heap and as such stores an amount of text thats unknown at compile time. You'd do this like so: `let s = String::from("hello");` This kind of string can be mutated, whereas the string literal cannot. This is due to how memory is dealt with.

TLDR:

`&str` is an immutable pointer to a string somewhere in memory, whereas the `String` type stores a heap-allocated string that you're allowed to mutate.

## Memory and Allocation

With a string literal, we know its contents at compile time so the text is hardcoded directly into the final executable. With the `String` type, we allocate some memory on the heap to accomodate a dynamic, changing value. This means that:

- Memory must be requested from the allocator at runtime.
- This memory must be returned when we're done with it.

We do the first part with `String::from`. In languages with GCs, the GC keeps track and cleans up memory that isn't being used anymore, or without GC the programmer has to release it.

Rust is different, memory is automatically returned once the variable that owns it goes out of scope.

## References and Borrowing

Say, if we wanted to calculate the length of a string, we'd need to do something like this:

```rust
fn main() {
    let s1 = String::from("hello");
    let (s2, len) = calculate_length(s1);
}

fn calculate_length(s: String) -> (String, usize) {
    let length = s.len();

    (s, length)
}
```

This sorta sucks. So instead we'd use references. The issue with the above is we have to return the String to the calling function. You can instead use a reference like this:

```rust
fn main() {
    let s1 = String::from("hello");
    let len = calculate_length(&s1);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}
```

In Rust, ampersands are *references*, and they let you refer to some value without taking ownership of it. We call having references as function parameters *borrowing*. We cannot modify something that we're borrowing, unless we pass it into a function as `&mut`.

## The Slice Type

Slices let you reference a contiguous sequence of elements in a collection rather than the whole collection.