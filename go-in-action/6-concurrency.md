# Concurrency
It's best to write code that runs synchronously, but sometimes it doesn't work out that way. For example, with a web server it's useful to have multiple requests hit individual sockets.

In Go, concurrency is the ability for functions to run independently of each other. When a function is created as a goroutine it's treated as an independent unit of work that gets scheduled and executed on an available logical processor. The Go runtime scheduler manages all goroutines, sitting on top of the OS it binds an OS's threads to logical processors which execute goroutines.

Concurrency synchronization comes from a paradigm called *communicating sequential processes*, which is a message-passing model that communicates data between goroutines. The key data type for synchronizing and passing messages is called a *channel*, which makes it easier to write concurrent programs and makes them less prone to errors.

## Concurrency vs parallelism
When you run an app, your OS starts a process for it. It's like a container that holds all the resources an app uses and maintains as it runs. The resources include things like a memory address space, handles to files, devices and threads. A thread is a pth of execution that's scheduled by the OS to run the code that you write. Each process contains at least one thread, with the initial one being called the **main thread**. When the main thread terminates, the app terminates because this path of execution is the origin for the app. The OS schedules threads to run against processors regardless of the process they belong to.

The OS schedules threads to run against physical processors and the Go runtime schedules goroutines to run against logical processors. Each logical processor is individually bound to a single OS thread.

Concurrency is not parallelism. Paralellism can only be achieved when multiple pieces of code are executing simultaneously against different physical processors. Parallelism is about doing lots of things at once, whereas concurrency is about managing a lot of things at once.

## Goroutines
For example, we can declare an anaonymous function like

```go
go func() {
  // schedule the call to Done to tell main we're done, as defer is called when a function ends
  defer wg.Done()

  do_stuff...
}
```

## Channels
Channels let you share resources between goroutines. You use `make` to create a channel, like so:
```go
unbuffered := make(chan int)
buffered := make(chan string, 10)
```

Making a channel requires the keyword `chan` and then the type of data the channel will allow to be exchanged. If you're creating a buffered channel then you specify the size of the buffer as the second argument.

You send a value into a channel by going like this:
`buffered <- "Gopher"` and for another goroutine to receive that string, we go like
`value := <- buffered`

### Unbuffered channels
An unbuffered channel is a channel with no capacity to hold any value before it's received. These types of channels require both a sending and receiving goroutine to be ready at the same instant before any send or receive operations can complete. If one isn't ready, the channel makes the first goroutine wait. Think of it like two people in a relay passing a baton. The baton will only be passed when both people are ready.

### Buffered channels
A buffered channel is a channel with capacity to hold one or more value before they're received. These types of channels don't force goroutines to be ready at the same isntant. A receive will block only if there's no value in the channel to receive, and a send will only block if there's no available buffer to place the value being sent. This leads to the biggest difference between buffered and unbuffered, which is that an unbuffered channel provides a guarantee that an exchange between two goroutines. Buffered channels are basically a queue, so think of them like that.