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