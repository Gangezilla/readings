# Standard Library

The Go standard library is a set of core packages that enhance and extend the language.

There's heaps of packages, well over 100 packages in 38 categories. You can see aaaaaaall of them here <https://golang.org/pkg/>

The source code for the standard library is precompiled as part of your Go distribution package.

Let's look at a few:

## Logging

It's common practice to write logs to `stdout` and errors to `stderr`. The log package lets you write your own logging functions too.

In saying that, there's a bunch of logging libraries that we'll probably use instead...

## Encoding/Decoding

You can handle JSON data in Go with the `encoding/json` package.

```go
import "encoding/json"
...
var gr gResponse
json.NewDecoder(resp.Body).Decode(&gr)
fmt.Println(gr)
```

Blah blah, the book covers input and output, but it's not too important for me. I'll figure it out as I go.
