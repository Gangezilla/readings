## Mark-sweep garbage collection

We'll assume the mutator is running on one or more threads but that there's a single collector thread. All mutator threads are stopped while the collector runs, which is called *stop-the-world*. This approach simplifies the construction of collectors considerably.

- From the perspective of the mutator threads, collection executes atomically, so no mutator thread will see any intermediate status of the collector.
- We assume each mutator thread is stopped at a place where it's safe for the collcetor to examine its memory.
- Stopping the world gives us a snapshot of the heap, so we don't have to worry about mutators rearranging the topology of objects while the collector is trying to determine which objects are live.
- The goal of an ideal garbage collector is to reclaim the space used by every object that will no longer be used by the program, so it has three tasks. 
  - allocate space for new objects
  - identify live objects
  - reclaim the space occupied by dead objects
- These tasks aren't independent, cos the way space is reclaimed affects how fresh space is allocated.
- Mark-sweep has two phases. First, the collector traverses the graph of objects starting from the roots (registers, thread stacks, global variables) through which the program might immediately access objects, then following pointers and *marking* each object that if finds, which is called *tracing*. The second *sweeping* phase, the collector examines every object in the heap and reclaims every unmarked object.
- Mark-sweep is an *indirect collection* algorithm. It doesn't detect garbage, but identifies live objects and then concludes that anything else must be garbage.

## The mark-sweep algorithm

- From the viewpoint of the GC, mutator threads perform three operations of interest, *New*, *Read* and *Write*. The mark-sweep interfaces with the mutator in a very simple way, if a thread is unable to allocate a new object, the collector is called and the allocation request is retried.
- If there is still insufficient memory available to meet the allocation request then heap memory is exhausted, which is often a fatal error.
- Before traversing the object graph, the collector must prime the marker's work list with starting points for traversal. Each root object is marked and added to the work list, and it's marked by setting a bit/byte in the object's header or in a side table.
- If an object can't contain pointers then it has no children so doesn't need to be added to the work list.
- Marking the graph of live objects is straightforward, references are removed from the work list and the targets of their fields marked until the work list is empty.
- At this point, every object reachable from the roos will have been visited and it's mark-bit will have been set. Any unmarked object is therefore garbage and the marking phase is complete.
- The sweep phase returns unmarked nodes to the allocator. Usually the collector sweeps the heap linearly starting from the bottom up, freeing unmarked nodes and resetting the mark-bits of marked nodes in prep for the next collection cycle.
- Mark-sweep collector imposes constraints on the heap layout.
  - First the collector doesn't move objects, so the memory manager must be careful to try to reduce the chance the heap becomes so fragmented that the allocator struggles to meet new requests as this would lead to the collector being called too frequently or preventing allocation. 
  - The sweeper must also be able to find each node in the heap. The sweeper must be able to find the next node even in the presence of padding introduced between objects to observe alignment requirements.

## The tricolour abstraction

- The tricolour abstraction is a useful characterisation of tracing collectors that permits reasonaing about correctness in terms of invariants that the collector must preserve.
- It partitions the object graph into black (presumed live) and white (possibly dead) objects.
- Initially every node is white. When a node is first encountered during tracing it is coloured grey when it has been scanned and its children identified, it is shared black. An object is black if the collector has finished processing it, grey if the collector knows about it but hasn't finished processing it (or needs to process it again).
- Tracing makes progress through the heap by moving the collector wavefront (grey objects) separating black objects from white objects until all reachable objects have been traced black.
- The algo preserves an important invariant, there are no references from black to white objects. Thus, any reachable white objects must be reachable from a grey object.
- Tricolour is most useful in a concurrent world, where mutator threads run concurrently with the collector.

## Improving mark-sweep

- An app's perf is often dominated by its cache behaviour. Caches improve performance because applications typically exhibit good *temporal locality*. If a memory location has been accessed recently, it's likely it will be accessed again soon and so it's worth caching its value.
- Apps may also exhibit good *spatial locality*, meaning a location's neighbours are likely to be accessed soon.

## Issues to consider

Mark-sweep is the first GC algo to be developed, but there's some appealing things about it:

- mutator overhead: mark-sweep imposes no overhead on mutator read and write ops. mark-sweep is commonly used as a base algo for more sophisticated collectors.
- throughput: mark-sweep offers good throughput. The mark phases is comparatively cheap and dominated by the cost of pointer chasing. It only needs to set a bit or byte on each live object, nothing gets moved. But, mark-sweep requires all mutators to be stopped while the collector runs.
- space usage: mark-sweep has pretty good space usage, but does require some headroom to operate in the heap
- to move or not to move: it's simpler not to move, but when you don't move, the heap in long running apps tend to become fragmented. many collectors use mark-sweep to manage the heap and then periodically defragment it.

## Questions

Why did Go pick this?
How does it defragment the heap?