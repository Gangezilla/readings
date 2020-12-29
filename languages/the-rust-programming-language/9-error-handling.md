# Error Handling

Rust groups errors into *recoverable* and *unrecoverable* errors. For a recoverable error (like a file not found) it's appropriate to report this to the user and retry. Unrecoverable errors are always symptoms of bugs, like trying to access a location beyond the end of an array. Rust has the `Result<T, E>` type for recoverable errors and the `panic!` macro for unrecoverable errors.

## Unrecoverable errors

When bad things happen you `panic!` and it makes your program print a failure message, unwind and clean up the stack and quit. Unwinding the stack means Rust walks back up the stack and cleans up data from each function it encounters, which is a lot of work. If you need to make your binary really small you can abort instead of panicking, letting the OS handle cleanup.

We can run a program with RUST_BACKTRACE to see the trace when it comes from a third party file like so `RUST_BACKTRACE=1 cargo run`

## Recoverable errors

When we want to recover from an error we can return a `Result<T, E>`. These are generics, with the `T` representing the type of the value that'll be returned with `OK` and the `E` representing the type of error that'll be returned with the `Err` variant.