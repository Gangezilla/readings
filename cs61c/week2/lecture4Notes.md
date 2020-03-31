# Lecture 4 - C Memory Management and Usage

## Recap

- Pointers are abstraction of machine memory addresses.
- Pointer variables are held in memory, and pointer values are just numbers that can be manipulated by software.
- In C, close relationship between array names and pointers.
- Pointers are powerful but dangerous

- String is just an array of characters.
- You tell how long a string is by finding the null character or 0 byte, '\0'.

## Valid Pointer Arithmetic

- Add an integer to a pointer
- Subtract 2 pointers (in the same array)
- Compare pointers (when you do this between two ints, it returns the result in an int and so forth)
- Compare pointer to NULL (indicating the pointer points to nothing)

## Arguments in main()

- To get arguments to the main function, use: `int main(int argc, char *argv[])`
- `argc` contains the number of strings on the command line
- `argv` is a pointer to an array containing the params
- `foo hello 87` = `argv[0] = "foo", argv[1] = "hello", argv[2] = "87"`

## C Memory Management

- We assume one program runs at a time with access to all of memory
- Later we'll discuss virtual memory which lets multiple programs all run at same time, each thinking they own all of memory.
- Program's _address space_ contains 4 regions.
  - _stack_: local variables inside functions, grows downward (stack is used to allocate variables inside of a function. every invocation of a function needs its own space to grow variables. When you return from a function, the stack goes back up and you free that space up. LIFO. For variables inside each function).
  - _heap_: space requested for dynamic data via malloc(); resizes dynaimcally, grows upwards (used for lumps of data you want to dynamically allocate, but that you want them to last for longer than an individual function.).
  - _static data_: Variables delcared outside functions, does not grow or shrink. Loaded when program starts, can be modified (everything you define outside of a C function).
  - _code_: loaded when program starts, does not change (instructions to the computer, the program)
- We grow the stack and heap in opposite directions to maximise the amount that either needs. If it crosses, you're in trouble cos you've run outta memory.

## Where are variables allocated

- If declared outside a function, allocated in "static" storage.
- If a variable is delcared inside a function, it gets allocated on the "stack" and freed when function returns.

## The Stack

- Every time a function is called, a new frame is allocated on the stack.
- Basically when you call a function, you have to remember where you came from. A stack frame includes this return address, local variables, as well as the arguments that are called with this function. You copy the variables into the stack frame.
- Stack frame is the storage you need for your function, and you need a new one of these for each function invocation.
- Last In, First Out (LIFO) data structure. When you call a function, the _stack pointer_ grows down. We allocate more space for the stack by changing the stack poitner to indicate where the bottom of the stack is.
- When the last function returns, you just move the stack pointer back up which allocates and deallocates the stack space.

## Managing the Heap

- The heap lets you dynamically create objects on the fly.
- C gives us 5 functions for heap management
- `malloc()` gives us a chunk of bytes in memory, takes one argument of the number of bytes. It's all uninitalized memory, all undefined bits, whatever was in there before.
- `calloc()` gives us a chunk of zeroed memory.
- `free()` which frees us space in memory
- `cfree()` dont use this!!
- `realloc()` change size of previously allocated block. realloc may not give you the same memory, it might copy the old values, but it'll give you the same block. This is problematic because if you have pointers that refer to this, your pointers all point to garbage. Be careful.

## Malloc()

- Takes one argument, the number of bytes you want. You need to make sure the argument here is big enough for all the bytes in memory. You can use `size_t` which will count the bytes inside of the machine, so a 32 bit machine will get a 32bit size etc.
- `malloc` returns to you a chunk of memory, it doesn't know what kind you want to put in there so it returns a void \* pointer. It's a very raw low level interface.
- Subsequent calls might not yield blocks in contiguous addresses.
- `sizeof` returns size of given type in bytes, produces more portable code. Makes sure that for this machine, you'll get a valid value.
- Returns `void*` pointer to block.
- `malloc` can return NULL if there's no memory, so you always need to check the return value of it.
- If you want to free the block, you have to use the exact same pointer value.

```c
int *ip;
ip = (int *) malloc(sizeof(int)); // (int *) is a cast from a void pointer to an int pointer.
typedef struct { .. } TreeNode;
TreeNode *tp = (TreeNode *) malloc(sizeof(TreeNode));
```

## Managing the Heap

- Once you're done you want to free the memory.
- `void free(void *p)` where p is pointer containing the address originally returned by `malloc()`
- NULL is always valid for any pointer type.
- You basically can't do any pointer arithmetic on a malloc pointer, cos malloc needs the exact same pointer it gave you.
- If you don't return the same pointer, some really bad stuff can happen.

## Observations

- Code, static storage are easy cos they never grow.
- Stack space is pretty easy, stack frame are created and destroyed in LIFO order.
- The heap is tricky, cos you can allocate and deallocate at any time.

## How are malloc and free implemented?

- Underlying operating system allows `malloc` library to ask for large blocks of memory to use in heap
- A very simple way of implementing malloc: You have a big chunk of memory, linked list of free space, and you iterate up and down through it. BUT you'd end up with fragmentation of your memory which means that it's inefficient but you'd also have wasted space.
- Malloc often has separate pools of blocks for different sized objects. "buddy allocators" always round up to power of 2 sized chunks to simplify finding and reusing chunks.
- Makes it easy to find and recover + merge them latest.
- We don't need to know how malloc works, it's pretty cool that C lets you do whatever you want, so you can write your own memory allocator to customise the memory allocator to a specific use case.
- Malloc has it's own data structure that keeps track of things, and thats why its important to return back a malloc pointer, otherwise it doesn't know what you're on about.

## Common Memory Problems

- Using uninitalised values. Unless you specifically say what memory is, it's not 0, and it will be some random values. Unless you specifically call `calloc`
- Using memory you don't own
  - Deallocated stack or heap variable
  - Out-of-bounds reference to stack or heap array
- Improper use of free/realloc my messing with the pointer handle
- Not checking for null
- Memory leaks (you allocated something you forgot to later free). You need the pointer malloc gave you, if you somehow lose that pointer, you've got no way of freeing memory up so your data just sits there slowly gradually occupying space.

## Questions

- When would I use calloc vs malloc
