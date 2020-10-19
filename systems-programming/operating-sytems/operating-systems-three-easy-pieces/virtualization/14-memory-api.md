# Interlude: Memory API

In Unix/C programs, how do we allocate and manage memory? What interfaces are commonly used? What mistakes should be avoided?

## Types of Memory

In C programs, there are two types of memory that are allocated. The first is called stack memory, and allocations and deallocations are managed implicitly by the compiler for you; because of this its sometimes called automatic memory. This is declared when you declare a variable like `int x;`. The compiler makes sure to make space on the stack when this function is called, and when you return the compiler deallocates the memory.

If you need longer lasting memory, you need to use the heap, where allocations and deallocations are handled by you.

## The `malloc()` call

`malloc()` is quite simple, you tell it how much room on the heap you want and it gives you back a pointer or fails and says NULL.

Generally you don't just pass in a number, you'd pass in something like this: `double *d = (double *) malloc(sizeof(double));` to specify you want space for a double-precision floating point value.

You have to be careful with strings, you should do like `malloc(strlen(s) + 1)` so you leave room for the end of string character.

## The `free()` call

Allocating memory is easy, knowing when to free it is the hard part. To free heap memory, we use `free()`

## Common Errors

Side note: when you use a keyword like `new`, that's kind of akin to calling malloc and allocating space on the heap.

### Forgetting to allocate memory

Some routines expect memory to be allocated before you call them, such as `strcpy`.

Just because a program compiled or even ran doesn't mean the program is correct.

### Not allocating enough memory

A related error is not allocating enough memory, which is sometimes called a buffer overflow.

What can happen is that a variable can overwrite the end of another value which is pretty bad. This is actually the source for a number of security vulnerabilities, so be careful with malloc sometimes.
