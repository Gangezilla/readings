# Traits and Generics

- Interfaces in Java help us group related functionality together

## Traits

- What can this type do?
  - Display
  - Clone/Copy
  - Iterator/Intolterator
- Allow us to override functionality
  - Drop
  - Deref
- Allows us to define default implementations
  - ToString (like if something implements display we can make it use this)
- Allow us to overload operators like + - * etc. This is useful if we want to define how to add two vectors together for example
- If we look back at our previous LL example we could implement a `Display` trait like this:

```rust
impl fmt::Display for LinkedList {
    ...
}
```

and then when we `println!` the LL it will use this function which is pretty cool