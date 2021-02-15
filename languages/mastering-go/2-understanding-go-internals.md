# Understanding Go Internals

## Garbage Collection

You can get some stats on garbage collection with the `runtime` package.

### Tricolor algorithm

The Go GC uses the tricolor algorithm. The tricolor mark-and-sweep algo essentially divides the objects of the heap into three different sets according to their color:

- black objects have no pointers to any object of the white set.
- white objects can have a pointer to an object of the black set, as this has no effect on the operation of the garbage collector.
- Grey objects might have pointers to some objects of the white set. 
- The objects of the white set are candidates for GC.
- Objects go from black to grey to white
- When GC begins, all objects are white, and the GC visits all *root* objects and colors them grey. Roots are objects that can be accessed by the application incl global variables and other things on the stack.
- After this, the GC marks a grey object as black and figures out if that object has pointers to other white objects. If this object has pointers to one or more white objects, its put back as grey. This keeps going as long as objects exist in the grey set.
- After this, white objects are unreachable and can be garbage collected.

Go garbage collection can also be applied to variables like channels.

### Go GC

Main concern of Go GC is low latency, so short pauses. The classic GC algo is called mark-and-sweep. The algo stops program execution (stop-the-world GC) so it can visit all the accesible objects in the heap and *marks* them, then it *sweeps* the inaccessible objects. When it's marking it marks them as white, grey or black. The sweeping begins when there are no grey objects left to examine.

This can add latency as it stops everything, Go tries to improve this by running it as a concurrent process. But, stuff gets added all the time which makes it a bit tricky for the GC. The solution is to make all new objects grey, so the grey set acts like a barrier between the white and black set.

### the defer keyword

`defer` postpones the execution of a function until the surrounding function returns. Deferred functions are executed in LIFO, so if you defer function 1, 2 and 3. They will both be executed in the opposite order they were called, so function 3, 2, 1.

If you wanna learn more about what's happening behind the scenes when you execute `go build`, add the `-x` flag to it.
