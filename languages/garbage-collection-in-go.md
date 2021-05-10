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
- Find the point in the source code where the GC is terminated when the program is and say what happens when it is (i imagine we just bin the heap, but confirm this...)
- Wrap up, i guess...

### Introduction

In this article I'm going to discuss memory management and how Go handles this. I'll start by giving a high level overview of memory management and then dive deeper into Go implements this by using a garbage collector. I've based this article on Go 1.16, so later versions may outdate some of this information.

As most programs run they write objects to memory. At some point these objects should be removed as they aren't needed anymore. In a language like C the programmer will call a function such as `malloc` or `calloc` to write an object to memory. These functions return a pointer to the location of that object in heap memory. When this object is not needed anymore, the programmer calls the `free` function to allow this use this chunk of memory again. This method of memory management is **explicit deallocation** and is quite powerful. It gives the programmer greater control over the memory in use, which allows for some types of easier optimisation. However, it leads to two types of programming errors.

One, calling `free` prematurely which creates a **dangling pointer**. Dangling pointers are pointers that no longer point to valid objects in memory. This is bad because the program expects a defined value to live at a pointer. When this pointer is later accessed there's no guarantee of what value exists at that location in memory. There may be nothing there, or some other value entirely. Two, the opposite, failing to free memory at all. If the programmer forgets to free an object they may face a **memory leak** as memory fills up with more and more objects. This can lead to the program slowing down or the program crashing if it runs out of memory. Unpredictable bugs can be introduced into a program when memory has to be explicitly managed.

This is why languages like Go offer **automatic dynamic memory management**, or just **garbage collection**. Languages like this offer benefits like:

- increased security
- better portability across operating systems
- less code to write
- runtime verification of code
- bounds checking of arrays

Garbage collection has a performance overhead, but it isn't as much as is assumed. The tradeoff is that a programmer can focus on the business logic of their program and ensure it meets the needs of the end user, instead of worrying about managing memory.

A running program will store objects in two locations in memory, the [**heap**](https://en.wikipedia.org/wiki/Memory_management#HEAP) and the [**stack**](https://en.wikipedia.org/wiki/Stack-based_memory_allocation).Garbage collection operates on the heap, not the stack. The stack is a data structure that stores values as they're defined in a function. Calling another function within a function will push a new [**frame**](https://en.wikipedia.org/wiki/Call_stack) onto the stack. This frame will contain the values of that function and so on. When that function return the stack frame corresponding to that function is popped off the stack. This is what you'll see when a running program crashes and you see a stack trace. The stack trace contains all the calling functions up to where your program got up to.

IMAGE OF STACK

In contrast, the heap contains values that are referenced outside of a function. For example, statically defined constants at the start of a program, or more complex objects, like Go structs. When the programmer defines an object that gets placed on the heap, the needed amount of memory is allocated and a pointer to it is returned. The heap is a big graph where objects are represented as nodes that are referred to in code or by another object. As a program runs, the heap will continue to grow as objects are added unless the heap is cleaned up.

IMAGE OF A HEAP AND HEAP GRAPH GOES HERE

Go [prefers to allocate memory on the stack](https://groups.google.com/g/golang-nuts/c/KJiyv2mV2pU/m/wdBUH1mHCAAJ), so most memory allocations will end up there. This means that Go has a stack per goroutine and when possible Go will allocate variables into this stack. The Go runtime attempts to prove that a variable is not needed outside of the function by performing **escape analysis** to see if an object "escapes" the function. If it's unclear that a variable only appears in one function, it will be allocated on the heap. Generally if a Go program has a pointer to an object then that object is stored on the heap. Take a look at this sample code:

```go
package main

type myStruct struct {
  value int
}

var testStruct = myStruct{value: 0}

func addTwoNumbers(a int, b int) int {
  return a + b
}

func myFunction() {
  testVar1 := 123
  testVar2 := 456

  testStruct.value = addTwoNumbers(testVar1, testVar2)
}

func someOtherFunction() {
  // some other code
  myFunction()
  // some more code
}

```

For the purposes of this example, let's imagine this is part of a running program. If this was the entire program the Go compiler would optimise this by allocating all variables into stacks. When the program runs:

1. `testStruct` is defined and placed on the heap in an available block of memory.
2. `myFunction` is executed and allocated a stack while the function is running.
3. When `myFunction` is being executed, `testVar1` and `testVar2` are both stored on the stack. When `addTwoNumbers` is called a new stack frame is pushed onto the stack with the two function arguments.
4. When `addTwoNumbers` finishes execution, the value is returned to `myFunction`. As this happens, the stack frame for `addTwoNumbers` is popped off the stack as it's no longer needed.
5. The pointer to `testStruct` is followed to the location on the heap containing it and `value` is updated.
6. `myFunction` exits and the stack created for it is cleaned up. The value for `testStruct` stays on the heap until garbage collection occurs.

ADD IMAGE OF STACK AND HEAP HERE

`testStruct` is now on the heap and without analysis, the Go runtime doesn't know if it's still needed. To do this, Go relies on a garbage collector. Garbage collectors have two key parts,  **a mutator and a collector**. The collector executes garbage collection logic and finds objects that should have their memory freed. The mutator executes application code and allocates new objects. It also updates pointers on the heap to point to different objects as the program runs. As part of this process, some mutator makes some objects unreachable when they're no longer needed.

ADD IMAGE OF PREVIOUS HEAP HAVING AN OBJECT BE CUT OFF. LIKE, ARROW GOING FROM ONE THING TO ANOTHER, LEAVING THE OLD THING STUCK OUT THERE.

Go's garbage collector is a **non-generational concurrent, tri-color mark and sweep garbage collector**. Let's break these terms down.

The [generational hypothesis](https://www.memorymanagement.org/glossary/g.html#term-generational-hypothesis) assumes that short lived objects are reclaimed most often. Thus, a generational garbage collector focuses on recently allocated objects. However, compiler optimisations allow the Go compiler to allocate objects with a known lifetime to the stack.[This means fewer objects will be on the heap, so fewer objects will be garbage collected.](https://groups.google.com/g/golang-nuts/c/KJiyv2mV2pU/m/wdBUH1mHCAAJ). This means that a generational garbage collector offers fewer benefits in Go.
[Concurrent means that the collector runs at the same time with mutator threads](https://github.com/golang/go/blob/master/src/runtime/mgc.go#L7). Therefore, Go uses a non-generational concurrent garbage collector. Mark and sweep is the type of garbage collector and tri-color is the algorithm used to implement this

A mark and sweep garbage collector has two phases, unsurprisingly named **mark** and **sweep**. In the mark phase the collector traverses the heap and marks objects that are no longer needed. The follow-up sweep phase removes these objects. Mark and sweep is an indirect algorithm, as it marks live objects, and removes everything else. This is a gif of how a mark and sweep collector works, [taken from here](https://spin.atomicobject.com/2014/09/03/visualizing-garbage-collection-algorithms/). There's other visualisations of other kinds of garbage collectors too.

**INSERT GIF IN HERE**

[Go implements this in a few steps:](https://github.com/golang/go/blob/master/src/runtime/mgc.go#L24)

Go has all goroutines reach a garbage collection safe point with a process called **stop the world**. This temporarily stops the program from running and turns a **write barrier** on to maintain data integrity on the heap. This fulfills concurrency by allowing goroutines and the collector to run simultaneously.

Once all goroutines have the write barrier turned on, the Go runtime **starts the world** and has workers perform the garbage collection work.

Marking is implemented by using a **tri-color algorithm**. When marking begins, all objects are white except for the root objects which are grey. A roots is an object that can the application directly accesses. The garbage collector begins marking by scanning stacks, globals and heap pointers.  When scanning a stack, the worker stops the goroutine and marks all found objects grey by traversing downwards from the roots. It then resumes the goroutine.

PICTURE OF SOME GREY NODES AND SOME WHITE NODES

The grey objects are then enqueued to indicate they're still live by turning them black.

PICTURE OF GREY NODES TURNING BLACK

The collector will then stop the world again and clean up all the white nodes that are no longer needed.

PICTURE OF WHITE NODES BEING COLLECTED

This process is initiated again once the program has allocated extra memory proportional to the memory in use. The `GOGC` environment variable determines this, and is set to 100 by default. [The Go source code describes this as:](https://github.com/golang/go/blob/master/src/runtime/mgc.go#L112):

> If GOGC=100 and we're using 4M, we'll GC again when we get to 8M (this mark is tracked in next_gc variable). This keeps the GC cost in linear proportion to the allocation cost. Adjusting GOGC just changes the linear constant (and also the amount of extra memory used).

Go's garbage collector improves your efficiency by abstracting memory management into the runtime. It's also one part of what enables Go to be so performant. Go has tooling to allow you to optimise how garbage collection occurs in your program, but it's out of scope for this article. For now, I hope you learnt a bit more about how garbage collection works generally and how it's implemented in Go.
## References

[The Garbage Collection Handbook](https://gchandbook.org/)
[Golang FAQ](https://golang.org/doc/faq#stack_or_heap)
[Getting to Go: The Journey of Go's Garbage Collector](https://blog.golang.org/ismmkeynote)
[Go: How Does the Garbage Collector Mark the Memory?](https://medium.com/a-journey-with-go/go-how-does-the-garbage-collector-mark-the-memory-72cfc12c6976)
[Garbage Collection in Go: Part 1](https://www.ardanlabs.com/blog/2018/12/garbage-collection-in-go-part1-semantics.html)
[Tracing garbage collection: Tri-color marking](https://en.wikipedia.org/wiki/Tracing_garbage_collection#Tri-color_marking)
[Golang: Cost of using the heap](https://medium.com/invalid-memory/golang-cost-of-using-the-heap-e70363469754)
[Implementing memory management with Golang’s garbage collector](https://hub.packtpub.com/implementing-memory-management-with-golang-garbage-collector/)
[Google Groups discussion, comment by Ian Lance Taylor](https://groups.google.com/g/golang-nuts/c/KJiyv2mV2pU/m/wdBUH1mHCAAJ)
[Memory Management Reference](https://www.memorymanagement.org)

## Required Images

Stack
Heap + graph
stack and heap
Visualisation of gc nodes, several images or a gif??

## Part 2

- More info on how to use this in Go to debug stuff. so you can run `GODEBUG=gctrace=1 ./app`. There's honestly heaps in here, so maybe do another article on how to debug Go programs and how to read the analysis, what to do with it. Bonus points if you find some optimisation in one of our apps tht you can improve and then discuss.
