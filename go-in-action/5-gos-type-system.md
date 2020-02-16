# Go's type system

Go is statically typed, so the compiler needs to know what the type is for every value. The compiler needs this to know how much memory to allocate, and what that memory represents.

## User-defined types

The best way to declare your own type is with a struct, like so:

```go
type user struct {
  name string
  email string
  ext int
  privileged bool
}

var bill user
```

or you can declare a variable of the struct type using a struct literal

```go
lisa := user(
  name: "Lisa",
  email: "lisa@email.com",
  ext: 123,
  privileged: true
)

```

You could also do this as a one liner, like `lisa := user("Lisa", "lisa@email.com", 123, true)`

- FYI, it's idiomatic to use the keyword `var` when a variable is being set to a zero value.
