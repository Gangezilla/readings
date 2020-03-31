## Lecture 2 Notes: C Intro, Pointers.

### Recap

- Review, two's complement. You invert all the bits and add one to get the negative number.
- Overflow is when magnitude of result is too big to fit into result representation.
- Both positive and negative numbers overflow. Underflow is for floating point numbers.
- Carry in = carry from less significant bits
- Carry out = carry to more significant bits.

- EDSAC first general stored program computer, idea of storing instructions as numbers in the computer. Basis of all modern computers, allows you to store your program in memory.

- Components of a computer:
- Processor: Control -> datapath
- Memory: Bytes
- Processor reads bytes from the memory and writes them back so on. Computer needs to do I/O. The program is just stored as numbers in memory, in the same location as data. Programs are just numbers held in memory.

- One of these great ideas is we have different levels of representation/interpretation. 1s and 0s are prety hard to program as, people used to do this omg. People then came up with assembly language which is a human readable text string that a program can read and convert into the equivalent binary patterns. This is still tediously low level.
- C is as close to assembly as we'll get. It's quite close to assembly, but is universal because it's portable. x86 and ARM are two totally different instruction sets, but you can write C and it can be compiled out on both.
- They still recommend the K&R C book, but I'm going to read through Modern C instead.
- C is very old, 40 years.
- C enabled a portable operating system, Unix. It's the number one choice for low level systems programming. Although this was one of it's primary uses, its still used a lot for applications.

- C takes a program which is a file on disk, and the compiler translates this into machine code in a process called compilation. This is unlike Java, which converts into architecture-independent bytecode. C is different because it compiles to the specific architecture.
- C creates an executable that will only work on one machine and OS.
- Advantage of doing it like C is it's super good performance.
- Reasonable compilation time, only need to recompile whats changed.
- People use C because it's low level access gives you access to the machine.
- Iteration process of "change -> compile -> run" can slow down your loop. But, Make rebuilds only changed pieces and can do compiles in parallel.
- Big builds would often be run overnight cos it takes a really long time.
- Not all of the work of translation si done by the compiler, but through the C pre-processor. This does a first pass at the text you type in and generates an intermediate file which goes to the compiler. it does stuff like removing comments, it also lets you include files `#include "file.h"`.
- All lines starting with `#` are C Pre-Processor (CPP) commands. Using a string goes to a path, using a `<stdio.h>` angle bracket tells the CPP to go to a standard location.
- You can also do conditional compilation if you're compiling for a different architecture.
- You can use `-save-temps` in gcc to see the result of preprocessing. You dont need to worry about this most of the time but its interesting.

- Header files are just pulled in and put in line. The compiler only looks at one file at a time.
- All variables in C are typed, like: int, unsigned int, long gives you a bigger integer
- The length of an integer in C depends upon the computer, so it could be 16, 32, 64 bits... The important thing was that the programmer can use whatevers natural to the machine. Flexible, but sometimes difficult to make the code portable.
- A short is guaranteed to be AT LEAST 16 bits. an int is guaranteed to be AT LEAST as big as a short or possibly bigger. a long is guaranteed to be AT LEAST 32 bits. all of them could be 64 bits. This is all valid C code, so you have to worry about this when being portable.
- `const` indicates that the value won't change.
- Enum, a group of related integer constants. `enum cardsuit {CLUBS, DIAMONDS, HEARTS, SPADES};` which will automatically set these to 0, 1, 2, 3.

- 'Compare "#define PI 3.14" and "const float pi=3.14" - which is true?
  A: Constants "PI" and "pi" have the same type. FALSE: #define sets the type as double whereas const is float.
  B: Can assign to "PI" but not "pi". FALSE: The pre-processor will have already put a value in there. The pre-processor will complain that PI has already been defined.
  C: Code runs at same speed with either. TRUE, depends on how you do it.
  D: "pi" takes more memory. FALSE a good compiler will make this irrelevant.
  E: They behave the same. FALSE
- Preprocessor was originally used when the compiler couldnt all be fit in memory, but we dont have this problem anymore.

- C is based around functions and they all have return values, like:

```c
int number_of_people()
{
  return 3;
}
```

- You can also specify the return type as void. They MUST be declared before they get used.
- Structs are structured groups of variables.

```
  typedef struct {
    int length_in_seconds;
  } Song;

  Song song1;

  song1.length_in_seconds = 233;

  Song song2;
  song2.length_in_seconds = 248;
```

- In the `stdio.h` library you get types for particular functions. Generates the correct code.
- When a C program starts

1. a C executable is loaded into memory by the OS
2. OS Sets up stack, then calls into C runtime library.
3. Runtime initialises memory and other libraries.
4. Then calls your `main()` function.

- In C 0 and NULL are false. There's no explicit boolean type. Everything else is true.
- Address vs Value. Consider memory to be a single huge array where each cell of the array has an address associated with it, and each cell also stores a value. You use an unsigned integer for the addresses.
- Don't confuse the address referring to a memory location with its value.
- An address refers to a particular memory location.
- A pointer is just a variable that contains the address of a variable.

- We declare a pointer by saying the value that the pointer will point to, like this:
- `int *x` which tells the compiler that variable x is address of an int.
- `x = &y` which says that x is now equal to the position in memory of y.
- `z = *x` tells the compiler to assign value at address in x to z. `*` is called the "dereference operator" in this context.

```
  int *p, x;
  x = 3;
  p = &x;
```

- The dereference operator gets the value that the pointer points to.
- `*p = 5` says that we want to put the value 5 into the address contained in this pointer. In this example, this will make x equal to 5.
- If you really want to change something you need the pointer. So `*p = *p + 1` that adds one to the value contained in the address of p.
