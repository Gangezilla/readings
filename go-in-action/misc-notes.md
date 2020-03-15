# Misc Go bits that don't fit anywhere else

FYI, we use a `...` notation in here. In Go, this can be a few things: https://programming.guide/go/three-dots-ellipsis.html. In this context it's used to indicate that we're passing a slice into the function.

`interface{}` is known as the empty interface. It's used by code that handles values of unknown type. 

Print out a map like this:

```go
for k, val := range directions {
      fmt.Println(k, "-", val)
  }
```

If you need to sort a slice with a function, like the JS sort method, you can use `sort.Slice` like so:

```go
sort.Slice(numbers, func(i, j int) bool) {
  return blah blah...
}
```

This also shows you can do anonymous functions too, neat.

## Pointers
Because you ALWAYS forget how pointers work:

A pointer holds the memory address of a value.

The type `*` is a pointer to a value, with it's zero value being nil. You use it like this:

`var p *int`

This means that the variable p **points** to an integer value.

The `&` operator generates a pointer to its operand, with the `*` operator denoting the pointer's underlying value.

```go
i := 42
p = &i

fmt.Println(*p) // read the i value through the pointer
*p = 21 // set the i value through the pointer p
```

When you set the value through a pointer, this is what **dereferencing** is.
