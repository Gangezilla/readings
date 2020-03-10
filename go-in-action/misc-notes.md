# Misc Go bits that don't fit anywhere else

FYI, we use a `...` notation in here. In Go, this can be a few things: https://programming.guide/go/three-dots-ellipsis.html. In this context it's used to indicate that we're passing a slice into the function.

`interface{}` is known as the empty interface. It's used by code that handles values of unknown type. 