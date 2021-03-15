# Garbage Collection In Go

## Part 1 - Semantics

- GCs track heap memory allocations, freeing up alloations that are no longer needed and keeping allocations that are still in-use.
- Understanding implementation details doesn't really matter, but having a good working model of how the GC for your language behaves does.
- Go uses a non-generational concurrent tri-color mark and sweep collector.
- The heap is not a container that you can store or release values from. It's important to understand that there's no linear containment of memory that defines the heap. Any memory reserved for app use in the process space is available for heap memory allocation. Think that any memory reserved for application use is available for heap memory allocation.

### Collector Behaviour

- Collector runs through 3 phases of work when collection starts.
  - Mark setup (stop the world). **First activity is turning on the Write Barrier** The write barrier allows the collector to maintain data integrity on the heap during a collection since both the collector and application goroutines will be running concurrently. To turn the write barrier on, every app goroutine is stopped, which is pretty quick at 10-30 microseconds. The only way for this to happen is when a function call occurs, because this is a guaranteed safe point.
  - Marking (concurrent). Once the write barrier is on, the collector begins marking. The collector first takes 25% of the available CPU 

[https://www.ardanlabs.com/blog/2018/12/garbage-collection-in-go-part1-semantics.html]

What does your blog post look like?
I want people to be able to walk away understanding what garbage collection is, how GC works within Go (so like a timeline view of whats happening), and to have a greater understanding of what their running application looks like.

## Blog post - An introduction to Garbage Collection in Go

I want to be able to introduce somebody (like me) to the concept of garbage collection and how it works within the context of Golang. I want them to understand how and why garbage collection happens, and be able to point to relevant bits of code to dive deeper if they wish.

- Intro paragreaph, explaining what this article is about and what you'll walk away knowing.
- What is a garbage collector?
- Touch on managed languages, why you'd go for something like Go with GC, vs why you'd go without. C vs Go vs something like Rust. Tradeoffs!
- Type safety
- Brief explainer on stack vs heap memory explain that GC works on the heap.
- Can get bits of this from the GC handbook, tie this into language features that Go has (such as dynamically choose size of new objects = go uses slices)
- Comparing GC algorithms, safety, throughput, completeness/promptness, pause time/space overhead.
- Go uses a non-generational concurrent tri-color mark and sweep collector. Break down what each of those means.
- explain that a GC program is divided into two parts, mutator and collector, point to where in the Go code these are defined.
- Talk about what actually happens when the GC is running, bonus points if you can point to the place in the code where GC begins and is managed from.
  - Stop the world, write barrier, stopping every running goroutine.
  - This will mostly be discussing the mark sweep algorithm, point out that mark-sweep is an *indirect collection* algo, so it doesn't detect garbage, but identifies live objects and then concludes that what's left must be garbage.
  - Explain how tricolor works.
  - Explain why Golang picked this.
  - Talk about how Go defragments the heap, explain what defragmentation is why its a problem how Go avoids it etc. note: you dont know this yet, so figure it out lol.
- Find the point in the source code where the GC is terminated when the program is and say what happens when it is (i imagine we just bin the heap, but confirm this...)
- Wrap up, i guess...

### Introduction

In this article I'm going to talk about garbage collectors, and how they work within the context of the Go language. I would love you to be able to walk away from this article with a better understanding of what a garbage collector is, the tradeoffs we make in using one and how the garbage collector in Go works, as well as relevant places in the Go source code to dig further if you're keen. As of publishing date, Go 1.16 was the most up to date version of Go so that's what this is based on.

Most programs at some point will need to recover the storage used by objects that are no longer needed, as your computer has a finite amount of memory. In languages like C this is done through the process of **explicit deallocation**. This means that in C when you need to define a string you would use a function like `malloc` or `calloc` which gives you a pointer to the location of that string on the heap. Then, once the programmer is finished with this string they will call the function `free` to allow this chunk of memory to be used again. This method of memory management is quite powerful as it gives the programmer greater control over the memory being used by the program, which allows for some easier optimisations depending on the program. However, it leads to two types of programming errors.

One, creating a *dangling pointer* by freeing memory prematurely. This is bad because your program will expect a certain value to live at a pointer, such as a string. However, the programmer has no guarantee of what value now exists at that location in memory, meaning you'll get unpredictable results. Two, the opposite, failing to free memory at all. If the programmer forgets to free memory they'll be faced with a *memory leak*, which can lead to performance degradation or the program crashing completely if it runs out of memory. It's easy to make mistakes like this when you have to explicitly manage the memory of your program.

This is why many programmers use languages with automatic dynamic memory management, such as Go. Languages like this offer a number of benefits, such as increased security, better portability across operating systems, less code to write, runtime verification of code, bounds checking of arrays and a number of other benefits. Automatic memory management does have a performance overhead, but it isn't as much as is commonly assumed. At the end of the day, this all means that programmers can spend more time writing the logic of their programs and making sure their program solves the needs of whatever end user will be using the program.

One of the important things to understand with garbage collection is it operates on the heap, and not the stack. The heap and the stack are two locations where data is stored by a running program. The stack generally refers to the call stack of a thread, which is a data structure that stores values as they're defined in a function. Each function call pushes a new frame onto the stack, and when those function calls return they pop a frame from the stack. This is what you'll see when a running program crashes and you see a stack trace. When you read through this stack trace you'll see all the calling functions up to where your program got up to.

The heap is another area of memory that stores values that need to be referenced outside of a called function. This can be statically defined constants at the start of a program, or more complex objects, such as Go structs. When the programmer defines an object that goes on the heap, the memory that object requires gets placed on the heap and a pointer to it is returned. Think about the heap as a big graph where the nodes are objects on the heap, which are referred to by some place in code or by another object. If unattended, the heap will continue to grow as more objects are added.

IMAGE OF A HEAP GRAPH GOES HERE

Go is a language that prefers to allocate memory on the stack, so most memory allocations will end up on the stack. This means that Go has a stack per goroutine and per function and when possible Go will allocate variables to a function's stack frame. The Go compiler will attempt to prove that a variable is not referenced after a function returns through a process called escape analysis. If the compiler cannot determine that a variable only appears in one function, it will allocate the variable on the heap. Generally if a Go program has a pointer to an object then that object is stored on the heap. Take a look at this sample code:

```go
type myStruct struct {
  value int
}

testStruct := myStruct{value: 0}

func addTwoNumbers(a int, b int) int {
  return a + b
}

func myFunction() {
  testVar1 := 123
  testVar2 := 456

  testStruct.value = addTwoNumbers(testVar1, testVar2)
}

myFunction()
```

First off, imagine that this segment of code is running as part of a bigger program. When the program runs, `testStruct` is defined and placed on the heap in an available block of memory. After this, `myFunction` is executed and allocated a stack while the function is running. When `myFunction` is being executed, `testVar1` and `testVar2` are both stored on the stack in a Last In First Out way. When we call `addTwoNumbers` a new stack frame is pushed onto the stack which includes the two values that are passed into it. Once `addTwoNumbers` is finished executing, the value is returned and the stack frame we just created is popped off the stack as we're finished with it. The pointer to `testStruct` is now followed to a location on the heap and the `value` field is updated. `myFunction` exits and the stack created for it is cleaned up. At this point, the value for `testStruct` stays on the heap and is assessed as part of the garbage collection process.

ADD IMAGE OF STACK AND HEAP HERE

At this point in the running program `testStruct` is on the heap and without any help, the Go runtime doesn't know if it still needs to be there or can be removed. To do this, we rely on a garbage collector. There's a number of approaches to garbage collection but one of the key concepts they have in common is this idea of a **mutator and a collector**. The collector runs the garbage collection functions and works to find objects that are unreachable so that they can be freed, and the memory can be reused by the running program. The mutator has the responsibility of executing application code. This includes allocating new objects and updating the pointers on the heap to point to different objects. In the process of updating the heap, the mutator will make some objects unreachable.

PROBABLY PUT THIS IN THE ABOVE PARAGRAPH => <https://spin.atomicobject.com/2014/09/03/visualizing-garbage-collection-algorithms/>

ADD IMAGE OF PREVIOUS HEAP HAVING AN OBJECT BE CUT OFF. LIKE, ARROW GOING FROM ONE THING TO ANOTHER, LEAVING THE OLD THING STUCK OUT THERE.

The garbage collector used by Go is a **non-generational concurrent, tri-color mark and sweep garbage collector**. 

Generational garbage collectors work off the assumption that most memory reclamations are made on short lived objects such as temporary variables, therefore it makes sense to spend more time looking at recently allocated objects. However, because Go prefers to allocate memory on the stack, Go generally has a larger proportion of objects that don't get placed on the heap so it doesn't need to rely on generational garbage collection. <https://groups.google.com/g/golang-nuts/c/KJiyv2mV2pU>  Concurrent means that it runs simultaneously with mutator threads <link to mgc.go goes here>. Therefore it is a non-generational concurrent garbage collector. Mark and sweep is the type of garbage collector and tri-color is the way that mark and sweep is implemented.

A mark and sweep garbage collector has two phases, unsurprisingly named **mark** and **sweep**. The mark phase has the collector traversing the graph of objects stored in the heap and marking objects that are no longer needed, and the sweep phase consists of removing objects that have been marked for removal. 

- tri-color: the algorithm used to implement mark and sweep behaviour.
- mark and sweep: the type of garbage collection

- Go uses a non-generational concurrent, tri-color mark and sweep garbage collector. break these terms down. one paragraph for all except tri-color mark and sweep.
- explain tri colour mark and sweep, make some diagrams too

pointers point to data allocated on the heap

- Stack and heap, GC works by managing the heap.
- There's a number of GC algorithms that are compared in a few categories. Go uses a GC algorithm called a **tricolor mark and sweep** algorithm.
- To be specific, Go uses a non-generational concurrent, tri-color mark and sweep garbage collector. We've already talked about the tricolor bit, explain non-generational concurrent.
- explain that a GC program is divided into two parts, mutator and collector, point to where in the Go code these are defined.
- Talk about what actually happens when the GC is running, bonus points if you can point to the place in the code where GC begins and is managed from.
  - Stop the world, write barrier, stopping every running goroutine.
  - This will mostly be discussing the mark sweep algorithm, point out that mark-sweep is an *indirect collection* algo, so it doesn't detect garbage, but identifies live objects and then concludes that what's left must be garbage.
  - Explain how tricolor works.
  - Explain why Golang picked this.
  - Talk about how Go defragments the heap, explain what defragmentation is why its a problem how Go avoids it etc. note: you dont know this yet, so figure it out lol.
- Find the point in the source code where the GC is terminated when the program is and say what happens when it is (i imagine we just bin the heap, but confirm this...)

## References

https://golang.org/doc/faq#stack_or_heap

## Part 2

- More info on how to use this in Go to debug stuff. so you can run `GODEBUG=gctrace=1 ./app`. There's honestly heaps in here, so maybe do another article on how to debug Go programs and how to read the analysis, what to do with it. Bonus points if you find some optimisation in one of our apps tht you can improve and then discuss.
