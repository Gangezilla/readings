# [Rusty Types]<https://cs140e.sergio.bz/notes/lec2/paper.pdf>

## Abstract

Languages close to the metal handle memory directly, and cos of this they're written in languages like C and C++. These languages lack and kind of guarantee on memory or race safety often leading to vulnerabilities and unreliable software.

This paper discusses Rusty Types and a type system that enables memory-safe and race-free references through ownership and restricted aliasing in the type system.

## What makes types Rusty?

### Linearity

Excluding immutable references, all Rusty Types behave lineraly, meaning exactly one binding to an object is allowed at any one point in the program. This means variables can not alias the same object. So if a binding attempts to alias an object with an existing variable, that variable becomes unusable and the object is _moved_ to the new variable and this new variable _owns_ the object.

```rust
let x = Vector([1, 2, 3]);
let y = x;
```

Here, the `Vector` initially owned by x is moved to y, meaning and appearance of `x` after the move is a type error.

### Memory Safety and Race Freedom

Rusty Types are designed for programs that use unmanaged, direct references to memory which allows them to be memory-safe and race-free.

Every storage location is guaranteed to have either:

- 1 mutable reference and 0 immutable references to it
- 0 mutable references and n immutable references to it

This invariant prevents races as it prohibits concurrent writers and readers to a single location.

Rusty Types also ensures each object has a unique binding, _the owner_ to prevent any dangling references.

```rust
let mut x = Vector([1, 2, 3]);
let y = &x[0];
clear(&mut x);
let z = *y;
```

Here, Vector is a container type that holds a pointer to a heap allocated array. The variable `x` is mutably bound to this vector . The `mut` annotation on x lets the variable `x` be rebound, and the vector to be mutated. `y` holds an immutable reference to the first element of the vector. The `clear` function deallocated the internal array. This program is not memory safe, and Rust will disallow it.

## (Re)borrowing

Borrowing is creating references from or creating a pointer to objects or their fieldds. Reborrowing is the same but through an existing borrow.
