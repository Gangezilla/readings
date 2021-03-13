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


Series of articles talking about how Go programs run, some articles on what they do when they’re running and then an article on how they get closed and cleaned up.

Articles:
- How does code get compiled
- How does a compiled program go to run on your computer (or a server), and how does it get closed?
- How does a program actually run on your computer, what things are happening in the background while it runs?
- 
What happens when a go programs starts? How does the OS schedule it, how is memory set aside for it.
Maybe in the context of k8s?

A new process is started for a program

- OS turns a program, our compiled Go code 
