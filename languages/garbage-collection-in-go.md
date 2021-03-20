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

In this article I'm going to talk about garbage collectors, and give you an overview of how the Golang garbage collector works. I'm aiming to give a high level view of memory management and how Go implements this through a garbage collector. At the moment, Go 1.16 is the most up to date version of Go so that's what this is based on. If you're reading this and a later version of Go has been released, some of this information may be outdated.

As any moderately complex program runs it will write objects to memory. At some point these memory objects will be cleaned up as they're no longer needed. For example, in C when the programmer defines a string they'll typically call function such as `malloc` or `calloc`. These functions return a pointer containing the location of that string in memory, but more specifically on the heap. Once the programmer is finished with this string they will call the function `free` to allow this chunk of memory to be used again. This method of memory management is called **explicit deallocation** and is quite powerful. It gives the programmer greater control over the memory being used by the program, which allows for some easier optimisations depending on the program. However, it leads to two types of programming errors.

One, calling `free` prematurely which creates a **dangling pointer**. Dangling pointers are pointers that no longer point to valid objects in memory. This is bad because the program expect a defined value to live at a pointer. If this pointer is then accessed later there's no guarantee of what value exists at that location in memory. There may be nothing there, or some other value entirely. Two, the opposite, failing to free memory at all. If the programmer forgets to free an object in memory they may face a **memory leak** as more and more objects are written to memory. This can lead to performance degradation or the program crashing if it runs out of memory. It's easy to introduce unpredictable bugs into a program when memory has to be explicitly managed.

This is why many programmers use languages, like Go, that offer **automatic dynamic memory management**, or just **garbage collection**. Languages like this offer a number of benefits like:

- increased security
- better portability across operating systems
- less code to write
- runtime verification of code
- bounds checking of arrays

Garbage collection does have a performance overhead, but it isn't as much as is commonly assumed. This means that programmers can spend more time writing the business logic of their programs and ensuring that it meets the needs of the end user.

The [**heap**](https://en.wikipedia.org/wiki/Memory_management#HEAP) and the [**stack**](https://en.wikipedia.org/wiki/Stack-based_memory_allocation) are two locations in memory where objects are stored by a running program. Garbage collection operates on the heap, not the stack. The stack is a data structure that stores values as they're defined in a function. Calling another function within a function will push a new [**frame**](https://en.wikipedia.org/wiki/Call_stack) onto the stack. This frame will contain the values of that function and so on. When that function return the stack frame corresponding to that function is popped off the stack. This is what you'll see when a running program crashes and you see a stack trace. The stack trace contains all the calling functions up to where your program got up to.

IMAGE OF STACK

In contrast, the heap contains values that need to be referenced outside of a function. For example, statically defined constants at the start of a program, or more complex objects, such as Go structs. When the programmer defines an object that is placed on the heap, the memory that object requires gets is allocated on the heap and a pointer to it is returned. Think about the heap as a big graph where nodes are objects referred to by a place in code or another object. As a program runs, the heap will continue to grow as more objects are added unless the heap is cleaned up.

IMAGE OF A HEAP AND HEAP GRAPH GOES HERE

Go is a language that prefers to allocate memory on the stack ***REFERENCE PLEASE***, so most memory allocations will end up on the stack. This means that Go has a stack per goroutine and when possible Go will allocate variables into this stack. The Go runtime attempts to prove that a variable is not needed outside of the function by performing **escape analysis** to see if an object "escapes" the function. If it's unclear that a variable only appears in one function, it will be allocated on the heap. Generally if a Go program has a pointer to an object then that object is stored on the heap. Take a look at this sample code:

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

For the purposes of this example, let's imagine this is part of a running program. If this was a program in isolation the Go compiler would optimise this to a degree where a heap wouldn't be required. When the program runs:

1. `testStruct` is defined and placed on the heap in an available block of memory.
2. After this, `myFunction` is executed and allocated a stack while the function is running.
3. When `myFunction` is being executed, `testVar1` and `testVar2` are both stored on the stack. When `addTwoNumbers` is called a new stack frame is pushed onto the stack which includes the two arguments.
4. Once `addTwoNumbers` is finished executing, the value is returned and the stack frame that was created is popped off the stack as it's no longer needed.
5. The pointer to `testStruct` is now followed to the location on the heap containing it and the `value` field is updated.
6. `myFunction` exits and the stack created for it is cleaned up. At this point, the value for `testStruct` stays on the heap and is assessed as part of the garbage collection process.

ADD IMAGE OF STACK AND HEAP HERE

`testStruct` is now on the heap and without analysis, the Go runtime doesn't know if it's still needed. To do this, Go relies on a garbage collector. There's multiple ways to implement garbage collection but one of the key concepts they all have is a **mutator and a collector**. The collector runs the garbage collection functions and finds objects that should have their memory freed. The mutator executes application code and has the job of allocating new objects, as well as updating pointers on the heap to point to different objects. As a program runs, the mutator will make some objects unreachable as they're no longer needed.

ADD IMAGE OF PREVIOUS HEAP HAVING AN OBJECT BE CUT OFF. LIKE, ARROW GOING FROM ONE THING TO ANOTHER, LEAVING THE OLD THING STUCK OUT THERE.

Go's garbage collector is a **non-generational concurrent, tri-color mark and sweep garbage collector**. Let's break these terms down.

Generational garbage collectors assume that short lived objects like temporary variables are reclaimed most often. Because of this, a generational garbage collector focuses on recently allocated objects. However, the Go compiler allocates objects which have a known lifetime to the stack. [This means that fewer objects need to be garbage collected so a generational garbage collector offers fewer benefits](https://groups.google.com/g/golang-nuts/c/KJiyv2mV2pU/m/wdBUH1mHCAAJ). [Concurrent means that the collector runs at the same time with mutator threads](https://github.com/golang/go/blob/master/src/runtime/mgc.go#L7). Therefore, Go uses a non-generational concurrent garbage collector. Mark and sweep is the type of garbage collector and tri-color is the algorithm used to implement mark and sweep.

A mark and sweep garbage collector has two phases, unsurprisingly named **mark** and **sweep**. The mark phase has the collector traversing the graph of objects stored in the heap and marking objects that are no longer needed, and the sweep phase consists of removing objects that have been marked for removal. A mark and sweep is an indirect garbage collection algorithm because it doesn't detect garbage but instead marks live objects and then knows that anything left over is garbage. This is a gif of how a mark and sweep collector works, [taken from here](https://spin.atomicobject.com/2014/09/03/visualizing-garbage-collection-algorithms/). If you're interested, there's visualisations of other kinds of garbage collectors too.

**INSERT GIF IN HERE**

**PROBABLY REWRITE THIS INTO STEPS BASED OFF THE COMMENT IN mcg.go**

The mark phase scans the heap to figure out which objects are needed by the application and which can be collected. But as we've previously established the Go garbage collector is **concurrent**. This means that the collector is running at the same time as the mutator so that new information could be added to the heap as the collector is running. This is bad because we could lose data integrity on the heap. To prevent this a **write barrier** is turned on. The write barrier prevents any more information being added to the heap by stopping the program for a short while. This is called **stop the world** time, and it is the first of two times that the collector stops the world. By stopping the world the collector looks at the heap at that moment in time and doesn't have to worry about the mutator changing it.

At this point the mark phase can begin the actual work of marking heap objects that are still being used. It does this by implementing a **tri-color algorithm**. When marking begins, all objects are considered white except for the root objects which are colored grey.

PICTURE OF WHITE WITH GREY ROOTS

The collector will traverse through the heap and color everything that it comes across as grey.

PICTURE OF SOME GREY NODES AND SOME WHITE NODES

The grey objects are then queued up to be turned black.

PICTURE OF GREY NODES TURNING BLACK

The collector will then stop the world again and clean up all the white nodes that are no longer needed.

PICTURE OF WHITE NODES BEING COLLECTED

The garbage in the heap has now been collected and the program will continue running again.

*CONCLUDING PARAGRAPH???*
## References

[The Garbage Collection Handbook](https://gchandbook.org/)
[Golang FAQ](https://golang.org/doc/faq#stack_or_heap)
[Getting to Go: The Journey of Go's Garbage Collector](https://blog.golang.org/ismmkeynote)
[Go: How Does the Garbage Collector Mark the Memory?](https://medium.com/a-journey-with-go/go-how-does-the-garbage-collector-mark-the-memory-72cfc12c6976)
[Garbage Collection in Go: Part 1](https://www.ardanlabs.com/blog/2018/12/garbage-collection-in-go-part1-semantics.html)
[Tracing garbage collection: Tri-color marking](https://en.wikipedia.org/wiki/Tracing_garbage_collection#Tri-color_marking)
[Golang: Cost of using the heap](https://medium.com/invalid-memory/golang-cost-of-using-the-heap-e70363469754)

## Part 2

- More info on how to use this in Go to debug stuff. so you can run `GODEBUG=gctrace=1 ./app`. There's honestly heaps in here, so maybe do another article on how to debug Go programs and how to read the analysis, what to do with it. Bonus points if you find some optimisation in one of our apps tht you can improve and then discuss.


