# mgc.go https://github.com/golang/go/blob/master/src/runtime/mgc.go

- Concurrent mark and sweep using a write barrier
- Steps
  - GC performs sweep termination.
    - Stop the world, making threads come to a GC-safe point. Sweep any unswept spans if this GC cycle was forced before the expected time.
  - GC performs the mark phase
    - Set `gcphase` to`_GCmark` from `_GCoff`
    - Prepare for mark phase, enabling write barrier, enabling mutator assists, enqueuing root mark jobs.
    - Start the world. From this point, GC work is done by mark workers started by the scheduler and by assists performed as part of allocation. The write barrier shares both the overwritten pointer and the new pointer value for any pointer writes (mbarrier.go). Newly allocated objects are immediately marked as black.
    - GC performs root marking jobs, incl scanning all stacks, shading all globals and heap pointers in off-heap runtime data structures. Scanning a stack stops a goroutine, shades any pointers on its stack and then resumes the goroutine.
    - GC drains the work queue of grey objects, scanning each grey object to black and shading all pointers found in the object.
  - GC performs mark termination
    - Set `gcphase` to `_GCmarktermination`
    - Stop the world.
    - Disable workers and assists, do housekeeping.
  - GC performs sweep phase
    - Set `gcphase` to `_GCoff`
    - Start the world, from now, newly allocated objects are white and allocating sweeps spans before use if neccesary.
  - Do it again when sufficient allocation has taken place
- Concurrent Sweep
  - The sweep phases proceeds concurrently with normal program execution. The heap is swept span-by-span both lazily (when a goroutine needs another span) and concurrently in a background goroutine (which helps programs that aren't CPU bound). At the end of STW mark termination all spans are marked as "needs sweeping".
  - The BG sweeper goroutine sweeps spans one by one.
- GC rate, next GC is after we've allocated an extra amount of memory proportional to the amount already in use. 
- 

## Questions

What's a write barrier?
Why is type accuracy important in a GC?
Non-generational???
What is a span?