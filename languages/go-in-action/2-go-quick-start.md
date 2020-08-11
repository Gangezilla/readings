# Go quick-start

## Program Architecture

- A `main` function must be decalred for the build tools to produce an executable, and it becomes the entry point for the program.
- The main function exists within a package called `main`. If this doesn't exist, the build tools won't produce an executable.
- In fact, every code file in Go belongs to a package
- Imports import code, giving you access to identifiers such as types, functions, constants and interfaces. You can import from a standard library or from like a github link...?
- Is there no package manager?

## The Main package

- The program's entry point can be found in the `main.go` code file.
- Every Go program that produces an executable has to have a `main` function, and has to have the name of the package its located in. If your `main` function isn't in your `main` package, the build tools won't produce an executable. Every code file in Go belongs to a package. In Go, a package defines a unit of compiled doe and their names help provide a level of indirection to the identifiers inside them, kinda like a namespace or a module in Elixir. This means you can distinguishj identifiers that are declared with the same name in different packages you import.
- Imports work as you'd expect, and you can import pacakges from the standard library, and can also bring in remote ones by slapping in a GitHub URL. In this context, they're in the same directory. But I imagine this is how we bring in external packages too.
  - How do we deal with version differences?
- This file also has an `init` function. In Go, `init` functions will always get called before the `main` function does.

## Search package

- The search package contains the framework and business logic for the program. In this context, a matcher is a value that contains speicif intelligence for processing a feed type. The program implements a default matcher, and also an RSS matcher which understands how to process RSS feeds.

### search.go

- Each code file in the search folder will contain `search` for the package name.
- In Go, if a variable name starts with an uppercase letter it is exported, and can be accessed by other packages when the package is imported. Conversely, if a variable name is lowercased, then it means other packages can't access these variables. In saying this, if an exported function's return value was an unexported variable, you'd be able to access this in other packages.

### Making a map

`make(map[string]Matcher)`

- A `map` is a reference type that you're required to `make` in Go. If you don't make the `map` first and assign it to your variable, you'll receive errors when you try to use the `map` variable, which is because the zero value for a `map` variable is `nil`.
- In Go, all variables are initialized to their zero value. For numeric types, that value is 0, for strings its an empty strings, for Booleans its false; and for pointers, the zero value is nil. When it comes to reference types, there are underlying data structures that are initialized to their zero values. But variables declared as a reference type set to their zero value will return the value of nil.

### More language features

- To declare a function in Go, use the keyword `func` followed by the function name, any parameters and then return values. For example, `func Run(searchTerm string) {}` declares a function with one string parameter.
- `feeds, err := RetrieveFeeds()` is a line that calls the `RetrieveFeeds` function, and this function returns two values. The first is a slice of `Feed` type values, with a slice being a reference type that implements a dynamic array. We use slices in Go to work with lists of data. The second return value is an error. Here we see that our functions can have multiple return values. It's common to declare a function that returns a value and an error. If an error occurs, never trust the other values.
- We also see a use of the short variable declaration operator, `:=`. This operator declares and initialises variables at the same time. The type of each value being returns is used by the compiler to determine the type for each variable.

  - You'll often see the short variable declartion use to redeclare variables. You'll see this frequently when dealing with errors as it avoids the need to declare differently named variables. You can see in the below example that we don't redefine error, which makes it easier to get whats going on. If we didn't do it like this, we'd probably do like `err1` and `err2` which sucks a bit. This is in context like so:

  ```go
    func Copy() {
      src, err := os.Open("blah")
      if (err != nil) {
        return
      }
      defer src.Close()

      dst, err := os.Create("blahblah")
      if (err != nil) {
        return
      }
    }
  ```

- A good rule of thumb with declaring variables is to use keyword `var` when declaring variables that will be initalised to their zero value, and to use the short variable declaration when you're initalising or calling a function.
- When the `main` function returns, the program terminates. Any goroutines that were launched and are running will be terminated. When writing concurrent programs, it's best to cleanly terminate any goroutines that were launched prior to letting the `main` function return.
- This program uses a `WaitGroup` from the `sync` pacakge to track all the goroutines we're going to launch.
- We define a loop like `for _, feed := range feeds {`, where the first argument is the index position, and the second is a copy of the value in that element. The keyword `range` is used to indicate what we want to iterate over. In the above loop, we use a blank identifier, `_`, to indicate that we're not interested in the index at this point.
- You've also got constants, which are declared like `const dataFile = "blah"`.
- In order to decode a data file like a JSON file, we need to define a struct for it:
  - This struct is an exported type that declares three fields that each map to a field name in the document.

```go
  type Feed struct {
    Name string `json:"site"`
    URI string `json:"link`
    Type string `json:"type"`
  }
```

- When we're declaring a function we specify it's output like so: `func RetrieveFeeds() ([] *Feed, error)`. Here, we have no input, and we return two values. The first return value is a slice of poitners to `Feed` values. The second return value is an error value that reports back if the function call was successful.
- I think one of the most important things in here is that you can return multiple things from a function, that's pretty cool. You just go `return feeds, err` and thats it.
- The keyword `defer` is used to schedule a function call to be executed right after a function returns. In this context it's used to close a file, and it's placed near the start of the function to reduce bugs and improve readability. It can go anywhere, really.

- UP TO PAGE 28
