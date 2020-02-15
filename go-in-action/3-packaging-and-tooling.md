# Packaging and tooling

## Pacakges

All Go programs are organisted into groups of files called pacakages, so that code has the ability to be included into other projects as smaller reusable pieces. Pacakges contain a series of related files with the `.go` extension, and provide clear separation of smaller units of code relating to implementation details. All `.go` files must declare the package they belong to as the first line of the file. Packages are contained in a single directory. You may not have multiple packages in the same directory, nor may you split a package across multiple directories.

### Package-naming conventions

The convention for naming your package is to use the name of the directory that it's in. The convention is to use short, concise, all lowercase names.

### Package main

The package `main` has special meaning in Go. It designates to the Go command that this package is intended to be compiled into a binary executable. It also looks for a function named `main()` to know what to execute.

### Imports

```go
import {
  "fmt"
  "strings"
}
```

### Remote imports

`import "github.com/spf13/viper`

### Named imports

```go
import {
  "fmt"
  myfmt "mylib/fmt"
}
```

## init

Each package can provide as many `init` functions as necessary.

```go
func init() {
  sql.Register("blahblah")
}
```

## Using Go tools

The `go` CLI command has a bunch of things in it:

- clean: will remove executables when you're done with them.
- vet: will lint and pick up errors
- fmt: formats your code
- doc _package_: will allow you to bring up documentation for something nice and quick.

## Dependency management:

There's a few solutions for this, but we'll figure out what work uses and then go with that.
