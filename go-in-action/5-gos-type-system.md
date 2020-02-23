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
- You can also declare a field in a struct with another struct:

```go
  type admin struct {
    person user
    level string
  }
```

## Methods

You can create functions on structs that allow you to extend their functionality. Two ways:

```go
// implementing method with a value receiver
func (u user) notify() {
  fmt.Printf("Blah blah"), u.name, u.email)
}
```

or

```go
// implementing a method with a pointer receiver
func (u *user) changeEmail(email string) {
  u.email = email
}
```

The parameter between `func` nd the function name is called a receiver, and it binds the function to the specified type. When a function has a receiver that function is called a method.

You'd use it like so:
```go
func (u user) notify() {}

bill := user("Bill")
bill.notify()
```

or you can do it using a pointer like so:

```go
lisa := &user("Lisa")
lisa.notify()
```

When deciding which one to use, think about this. If you need to create a new value, use value receivers. If you need to mutate the value use a pointer receiver.

### Built-in types
You've got your classic numeric, string and Boolean types.

### Reference types
slice, map, channel, interface and functions. When you declare a variable from one of these types, the value that's created is called a header value. They're called as such because they're essentially a pointer to an underlying data structure.

### Struct types
Struct types can represent data values that can be primitive or nonprimitive

### Interfaces
Polymorphism is the ability to write code that can take on different behaviour through the implementation of types. Once a type implements an interface, an entire world of functionality can be opened up to values of that type.
