# 4 Lifetimes, Ownership and Borrowing

Rust's borrow checker checks that all access to data is legal, allowing it to prevent safety issues. Learning how to work with the borrow checker allows you to build larger systems with confidence. It's part of the term "fearless concurrency".

Borrow checking relies on three concepts:

- **Ownership**, which relates to cleaning values up when they're no longer needed. For example, when a function returns, the memory holding its local variables needs to be freed. Owners cannot prevent other parts of the program from accessing their values or report data theft to some overarching Rust authority.
- A value's **lifetime** is the period when accessing that value is valid behaviour. A function's local variables live until the function returns. Global variables might live for the life of the program.
- To **borrow** a value means to access it. This is a bit confusing, cos you never have to "give it back". It's supposed to emphasise that a value has a single owner, but many parts of a program can access those values.

## Implementing a Mock Satellite 

The learning example for this chapter is a CubeSat constellation. CubeSats are mini satellites that increase the accessibility of space research. Ground stations are intermediaries between the operators and satellites. A constellation is the collective noun for satelites in orbit.

When you get an error like `value moved here` or `value used here after move` it can be a bit confusing. In the world of Rust, movement refers to **ownership**, rather than movement of data. Ownership is a term used within the Rust community to refer to the compile-time process that checks that every use of a value is valid and that every value will be destroyed cleanly.

Every value in Rust is **owned**. `sat_a`, `sat_b` and `sat_c` **own** the data that they refer to. When we call `check_status` with those values, ownership of the data moves from the variables in the `main` scope to the `sat_id` variable inside the function.

During the call to `check_status` ownership *moves* to the `check_status` function. When `check_status` returns a StatusMessage, it drops the `sat_a` value. The **lifetime** of `sat_a` ends here but it remains in the local scope of `main` after the first call to `check_status`.

### Special behaviour of primitive types

When we implemented the structs, the compiler starts getting mad at us. This is because primitive types implement the `Copy` behaviour. Types that implement `Copy` are duplicated at times that would otherwise be illegal. Primitive types are said to possess **copy semantics**, whereas all other types have **move semantics**.

## What is an Owner? Does it have any responsibilities?

In Rust, ownership is limited to an owner cleaning up when its values lifetimes end. When values go out of scope of their lifetimes end their destructors are called. A destructor is a function that deletes references to the code and frees memory. You can implement this yourself but most of the time shouldn't worry about it.

This implies that values may not outlive their owner. This means that a data structure built off references (like a linked list) is a bit more complex. If the root node of a tree owns the tree, it can't be removed without taking ownership into account.

## How ownership moves

There are two main ways to shift ownership from one variable to another. The first is assignment, and the second is passing data through a function barrier as an arg or return value.

Here we can see that `sat_a` starts its life with ownership over a CubeSat object.

```rust
fn main() {
    let sat_a = CubeSat { id: 0 };
}
```

The `CubeSat` object is passed to `check_status` as an arg, moving ownership to the local variable `sat_id`.

```rust
fn main() {
    let sat_a = CuebSat { id: 0 };
    ...
    let a_status = check_status(sat_a);
}
```

Another possibly could have been that `sat_a` relinquishes its ownership within `main()` to another variable

```rust
fn main() {
    let sat_a = CubeSat { id: 0 }
    ...
    let new_sat_a = sat_a;
}
```

We can fix the code we're working on by updating the `check_status` function to return the `sat_id` and resassigning the value of `sat_a` from that check_status function. This way, the lifetime value of `sat_a` is not dropped, but persists after it is used in this function.

## Resolving Ownership Issues

Rust's ownership system provides a route to memory safety without needing a garbage collector, but it's ownership system can trip you up if you don't know what's going on.

Four general strategies can help with ownership issues:

1. Use references where full ownership isn't required.
2. Duplicate the value.
3. Refactor code to reduce the number of long-lived objects
4. Wrap your data in a type designed to assist with movement issues.

We're going to extend our cubesat system so that each can receive and send messages.

### Use references where full ownership isn't required

Instead of requesting ownership, use a borrow in function definitions. For read-only access, use `& T`. For read/write access, use `&mut T`. Ownership might be needed in advanced cases, such as when functions wish to adjust the lifetime of their arguments.

With our new implementation, we make `Groundstation.send()` and `CubeSat.recv()` require mutable access to a `CubeSat` instance, as both methods are modifying the underlying `CubeSat.messages` vector. We move ownership of the message that we're sending into `messages.push` which provides us with some QA later, notifying us if we were 


### Use fewer long-lived values

If we have a large, long-standing object it can be unwieldy to keep this around for every component of your program that needs it. To do this, we'll create a function that returns CubeSat identifiers. When we need to communicate with a satellite we'll create a new object.

```rust
fn fetch_sat_ids() -> Vec<u64> {
    vec![1,2,3]
}

// a method for GroundStation to create a CubeSat instance
impl GroundStation {
    fn connect(&self, sat_id: u64) -> CubeSat {
        CubeSat {id: sat_id, mailbox: Mailbox {messages: vec![[]]}
        }
    }
}
```

### Duplicate the value

Having a single owner for every object can mean significant up-front planning and/or refactoring. An alternative to refactoring is to simply copy values. Don't do this all the time, but it can help in a pinch. Types can be opt into two modes of being copied: `Clone` and `Copy`. `Copy` acts implicitly whenever ownership would otherwise be moved so the bits of object a are replicated to create object b. `Clone` acts explicitly where Types that implement it have a `.clone()` method.

To implement `Copy`, your types must implement `Copy`. Integers and floating point numbers implement `Copy` but `String` and other tpyes don't. The reason is that a `String`s internal pointers would be duplicated, not the data those pointers refer to.

### Wrap Data within Specialty Types

A final strat is to use "wrapper" types that present a facade to the outside world of move semantics, but actually are doing something special under the hood. Rust lets programmers opt-in to runtime garbage collection. `Rc<T>` means a "reference counted type T". We ould wrap a single instance of `GroundStation` in a `Rc`, providing shared access to each of the satellites.

Setting this up involves a call to the `Rc::new()` static method