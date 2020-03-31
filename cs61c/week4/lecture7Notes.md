# MIPS Instruction Format - 2015-02-10

## Review: Allocating Space on Stack

- in C, automatic which is local variables inside a function and discarded when the function exits, and static where variables exist across exits from and entries to procedures.
- Use stack for automatic (local) variables that don't fit in registers. Helps you get around having 32 registers
- Procedure frame or activation record, segment of stack with saved registers and local variables
- `$fp` points to the start of the frame, you often don't need it though.
- Once I call a function it sets up it's activation frame. Caller doesn't know what's happening in a subroutine.
- when you call a function it sets up the activation frame, moves the stack pointer down, in MIPS the stack moves down.
- In MIPS you've got `$a0 - $a3` that hold arguments to a function. If you've got more than 4 arguments, you push it onto the stack. If it's a leaf function that doesn't call anything else, any other function that isn't has a return address. You need to remember this return address even though you're gonna call another function.
- In MIPS you've got this `jal` instruction, you need to remember your version of what goes in \$ra. Only need this if you're not a leaf function.
- Callee save register is something the caller expects not to be modified.
- Pieces of code that are compiled sepearately can call each other, means a debugger can step through the stack trace and figure out what called what.
- Stacktrace that gets sent back is what went wrong, which function did I die in and what were my arguments, this is the call path,

## Using the Stack

- Simply decrement the stack pointer, decrement the number of bytes you need
- I guess we use the stack cos it's easier than having to put all our values back, probably less brittle.

## Basic Structure of a Function

- We use a label to address a particular function.
- We can think of the way we do this in a few steps. You've got the prologue:
  - First thing we do is allocate space on the stack, then we push values onto the stack (typically the \$ra)
  - Body: Where we do all the work
  - Epilogue: Where we restore our registers, restore the return address, deallocate space on the stack.

## Where's the stack in memory?

- Stack starts in high memory and grows down
- MIPS programs 9text segment) in low end
- _Static data segment_ (constants and other static variables) above text for static variables.
- MIPS convention _global pointer_ \$gp points to static
- _Heap_ above static for data structures that grow and shrink; grows up to high addresses. Objects in the heaps are available at differing times based on when you allocate and free them.

## MIPS Memory Allocation

- Dereferencing a pointer that's a null pointer is a classic mistake. Heap lives on top of the static data and grows upwards, stack lives at the top and grows downwards.
- Register 1 is used by the assembler itself. Registers 26 and 27 are used by the OS, you can't rely on them.

## Big Idea: Store-Program Computer

- Really fast to do calculations, but it took days and days to reprogram it. Figured out that maybe they should just store the program in memory.

## Consequence #1: Everything Addressed

- Every memory location has an address. C pointers are just memory addresses: they can point to anything in memory.
- One register keeps address of instruction being executed: "Program Counter" (PC). it's really a pointer to an instruction. intel calls it an Instruction Pointer which is a better name
- The processor in your phone has a totally different bit encoding. If you want to run your C program on other processors you have to recompile. A machine is binary compatible with another if you can run it on another computer.
- IBM didn't think the PC was that important so they didn't lock any of it down. Used standard components and it meant people could clone them very easily. The whole PC industry came up because people could clone them really easily. PCs from today can still run programs from the early 80s cos they're binary compatible.
- MIPs is a bit newer, came out in the mid 80s. Part of this RISC wave, every instruction is 32 bits wide in MIPS. x86 processors have instructions of variable length.
- MIPS only sees 1s and 0s. 32 bits is the whole word. To define an instruction we have operands and operations which are different fields within a 32 bit operation.
- 1 layout for every instruction

- MIPS has R I and J instructions.
- I stands for Immediate, which allows us to put a number in there.
- J stands for Jummp
- R is everything else that has to do with register, the R stands for Register.
- 6 bits for the opcode

## R-Format Instructions

- Each R-format is separated into fields
- opcode: 6 bytes - partially tells us what instruction it is
- rs: 6 bytes - source register, usually used to specify register containing first operand
- rt: 6 bytes - target register, usually used to specify register containing second operand (name is misleading)
- rd; 5 bytes - destination register, usually used to specify register which will receive result of computation
- shamt: 5 bytes - this field contains the amount a shift instruction will shift by. Shifting a 32 bit word by more than 31 is useless, so this field is only 5 bits.
- func: 6 bytes
- MiPS instruction sert is mostly clean and orthoganal. MUltiply and divide instructions are encoded a bit differently in MIPS.
- If you shift more than 32 all the bits disappear, so do between 1 and 31.
- Shouild find a green card insert for MIPS which has all the instructions. Called a green card cos the IBM 360 had a cheat sheet that was green too.
- Each mIps instruction gets saved in memory as binary and then gets executed.
- They get to be a bit relaxed cos it makes it easier to execute. Focused on making the machines simple so it can run fast.
- This is just one convention for how software can be encoded. x86 vs ARM is very different.
- Its a bit hard to write 32bits as binary, so you'd usually just use a hex value, that way its only two numbers.

## Instructions with Immediates

- 5 bit field only represents numbers up to the value 31: immediates may be much larger than this.
- Ideally MIPS would have only one instruction format, unfortunately we need to compromise.
- Fewer operations that have immediates. Half of the instruction is taken up by the 16 bit immediate.

I didn't listen to the rest of this lecture, it's pretty hard to follow cos the recording is busted. But also, it's mostly showing how much space things take up in memory and it doesn't seem too relevant. If we need to know that maybe we can dig back in at some stage.
