# Introduction

## Intro

- Devs turn to managed languages and run-time systems cos they offer increased security an are more flexible cos they're abstracted away from the OS.
- Managed code offers benefits cos many services are provided by the VM so there's less code to write, code is safer cos the run-time verifies code as it is loaded, checks for resource access violations and bounds of arrays and manages memory automatically.
- Deployment costs are lower because you can deploy to different platforms easily.
- These all mean programmers can spend more time on the logic of their application.

- Almost all modern languages use dynamic memory allocation, meaning objects can be allocated and deallocated even if their total size wasn't known at the time that the program was compiled, and if their lifetime may exceed that of the subroutine activation that allocated them. A dynamically allocated object is stored in a *heap* rather than on the *stack* (or stack frame of the procedure that allocated it) or *statically* (where the name of an object is bound to a storage location that is known at compile or link time).
- Heap allocaton is important because it let the programmer
  - dynamically choose the size of new objects (avoiding program failure by exceeding hard-coded array limits)
  - use recursive data structures like lists, trees and maps
  - return newly created objects to the parent procedure (like factory methods)
  - return a function as the result of another function
- Heap allocated objects are accessed through references, typically pointers (reference to an address in memory of the object). This is sometimes through a handle which points to the object and can be relocated.

## Explicit deallocation

Programs need to recover the storage used by objects that are no longer needed. Memory used by heap objects can be reclaimed using *explicit deallocation* (think C's `free`) or automatically by the run-time system using reference counting or a garbage collector. Manual reclamation can lead to two kinds of errors.

1. Memory being freed prematurely while references exist to it creates a dangling pointer. These are really hard to debug and can lead to pretty unexpected behaviour.
2. An object may be failed to be freed by the program when it's no longer needed, which creates a memory leak. These can be benign in small programs but can lead to extreme performance degradation in bigger programs.

Errors like this are prevalent when two or more subroutines may hold references to an object, or when multiple threads reference an object. Theres a number of strategies to deal with this.

a -> b -> c
if object B is freed, the live object a contains a dangling pointer meaning the space occupied by C has leaked because C is not reachable and cannot be freed.

## Automatic dynamic memory management

Automatic dynamic memory management resolves many of these issues. GC prevents dangling pointers being created, as objects are only reclaimed when there's no pointer to it from a reachable object. In principle, all garbage is guaranteed to be freed, with two caveats.

1. *Tracing collection* defines garbage differently, and may not include all objects that will never be accessed again.
2. Some GC implementations may choose for efficiency not to reclaim some objects.

The key argument in favour of garbage collection is not just that it simplifies coding, but that it uncouples memory management from your code, improving reusability. It's not a silver bullet though, it can't guarantee the absence of space leaks or prevent a data structure from growing without limit. 

## Comparing garbage collection algorithms

It's impossible to have a "best" collector, but we can compare them based on a few metrics.

- Safety: Prime consideration is a GC should be *safe*, meaning it never reclaims the storage of live objects. This does come at a perf cost though.
- Throughput: Overall time spent in GC
- Completeness and promptess: *Complete* being all garbage in the heap should be reclaimed, *promptness* being the number of GC cycles required to do this in.
- Pause time: 

**Questions**

**What is `link time`?**
Link time is when the linker is working. Duh. The linker takes one or more object files and compiles them into a single executable. so it goes compile time -> link time -> runtime