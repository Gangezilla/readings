# Introducing Go
## Solving modern programming challenges with Go
Devs often have to choose between rapid perf with a language like C, and rapid development with a language like Ruby. Go bridges these worlds and offers a high-perf, fast to develop in language.

### Development Speed
Go offers really fast compiles by using a smart compiler and simplified dependency resolution algorithms. Go apps compile in under a second usually. Writing applications in dynamic languages makes you productive quickly because there are no intermediate steps between writing code and executing it. The trade-off is that dynamic languages don't offer the type safety that static langs do. Go's compiler catches type differences for you, unlike plain JS.

### Concurrency
Go's concurrency is one of its strongest features. Goroutines are like threads but use less memory and less code. Channels are data structures that let you send typed messages between goroutines with synchronization built in. This facilitates a programming model where you send data between goroutines.

#### Goroutines
Goroutines are functions that run concurrently with other goroutines. In other languages you'd use threads and have to write a lot of code to do so. In Go, the net/http library has concurrency built in using goroutines. Goroutines use less memory than threads and the Go runtime will automatically schedule the execution of goroutines against a set of configured logical processors. Each logical processor is bound to a single OS thread, making your app more efficient with less dev effort. It's pretty easy to do too:

```go
func log(msg string) {
  // some logging code here
}

go log("something bad")
```

The `go` keyword is all you need to schedule the log function as a goroutine, which allows you to execute other stuff asynchronously.

#### Channels
Channels are data structures that enable safe data communication between goroutines. Channels help you avoid problems typically seen in programming languages that allow shared memory access.
The hardest part of concurrency is ensuring your data isn't unexpectedly modified by concurrently running processes, threads or goroutines. Channels help to solve this problem by providing a pattern that makes data safe from concurrent modification.

### Go's type system
Go provides a flexible type system to encourage code reuse. Go devs embed types to reuse functionality in a design pattern called `composition`. In Go, types are composed of smaller types which is in contrast to inheritance based models.
Go has simple types like `int` and `string`.

### Memory Management
Go has a garbage collector so you don't have to worry about allocating and deallocating memory.

## Hello, Go
```go
package main

import "fmt"

func main() {
  fmt.Println("Hello World!")
}
```
- Import allows you to use external code. The fmt package provided by the standard library allows you to format and output data.
- The main function is what gets executed when you run your application, just like C.
