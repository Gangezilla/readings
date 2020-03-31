# Section 2.1 - Introduction

- The words of a computer's language are called _instructions_, and its vocabulary is called an _instruction set_.
- Computer languages are more akin to regional dialects than totally different languages.
- We're mostly looking at the MIPS instruction set, but we look a bit at the ARMv7, ARMv8 and x86 instruction sets.
- Instruction sets are all similar because computers are constructed from hardware technologies based on similar underlying principles.
- The goal of this chapter is to teach an instruction set that shows how its related to the hardware and also to a higher level programming languages.
- By learning how to represent instructions, you will also discover the secret of computing: the _stored-program concept_, which is the idea that instructions and data can be stored in memory as numbers.

# Section 2.2 - Operations of the Computer Hardware

- Every computer must be able to perform arithmetic and in MIPS we do it like so:
  `add a, b, c`
  This instructs a computer to add the two variables b and c and put the sum into a.
- The notation is rigid in that each MIPS instruction performs only one operation and must always have 3 variables.
- Suppose we want to place the sum of four variables b, c, d and e into variable a, which you'd do like so:

```asm
  add a, b, c # a = b + c
  add a, a, d # a = a + d
  add a, a, e # a = a + e
```

- Thus it takes three instructions to sum up these four variables.
- All MIPS instructions have three operations, and they're pretty simple? There's a few categories of arithmetic, loading and storing, logical operations and jumps.

**Design Principle #1: Simplicity favours regularity**
Here's two examples of C code and then assembly code:

```c
  a = b + c;
  d = a - e;
```

The translation from C to MIPS is performed by the compiler. The MIPS code would look something like this:

```asm
add a, b, c
sub d, a, e
```

```c
f = (g + h) - (i + j);
```

For this, the compiler must break the statement into several instructions

```asm
add t0, g, h # temp variable t0 contains g + h
add t1, i, j # temp variable t1 contains i + j
sub f, t0, t1 # f gets result of t0 - t1
```

# Section 2.3 - Operands of the Computer Hardware

- With assembly, you're restricted to what you can do because you can only store results in special hardware locations called registers.
- The size of a register in MIPS is 32 bits, groups of 32 bits occur so frequently they are given the name **word** in the MIPS architecture.
- We have 32 registers because of our second principle

**Design Principle #2: Smaller is faster**

- A very large number of registers may increase the clock cycle time simply because it takes electronic signals longer when they must travel farther.
- The MIPS convention is to use two character names after a dollar sign to represent a register.
- This means the above code looks like this:

```asm
add $t0, $s1, $s2 # temp variable t0 contains g + h
add $t1, $s3, $s4 # temp variable t1 contains i + j
sub $s0, $t0, $t1 # f gets result of t0 - t1
```

## Memory Operands

- The processor can keep only a small amount of data in registers, but computer memory contains billions of data elements, making it perfect for data structures like arrays and structures to be held in memory.
- MIPS therefore must contain instructions to transfer data between memory and registers. These instructions are called **data transfer instructions**. To access a word in memory, the instruction must supply the memory address. Memory is just a large, single dimensional.
- The data transfer instruction that copies data from memory to a register is called a load. For example:

```c
g = h + A[8];
```

\$s3 is the starting address of the array.

```asm
lw $t0, 8($s3) # temp reg $t0 gets A[8]
add $s1, $s2, $t0 # g = h + A[8];
```

- We multiply the starting address by the offset (8) to get the 8th position (i think).
- In addition to associating variables with registers, the compiler allocates data structures like arrays and structures to locations in memory.
- In MIPS, words must start at addresses that are multiples of 4. This is called an **alignment restriction** and many architectures have them.
- MIPS is big endian meaning we address it from the "big" side, ie left.
- The instruction complementary to load is called **store**, it ocpies data from a register to a memory, it's `sw` which stands for store word.
- Because the addresses in loads and stores are binary numbers, we can see why RAM for memory comes in binary sizes rather than decimals.

```c
A[12] = h + A[8];
```

in MIPS:

```asm
  lw $to, 32($s3) # temp reg $t0 gets A[8]
  add $t0, $s2, $t0 # temp reg $t0 gets h + A[8]
  sw $t0, 48($s3) # stores h + A[8] back into A[12]
```

- The process of putting less commonly used variables into memory is called _spilling registers_.
- Registers take less time to access and have a higher throughput than memory, it also uses less.

## Constant or Immediate Operands

- We can use `addi` to add a constant value, instead of having to pull that value from memory.

```asm
addi $s3, $s3, 4 # $s3 = $s3 + 4
```

- Operations with constants happen often, so doing it this way is faster instead of pulling this from memory.
- The constant zero has another role, which is to simplify the instruction set. For example, the move operation is just an add instruction where one operand is zero. Hence MIPS dedicates a register \$zero to be 0.

# 2.6 Logical Operations

- Operations to do bit manipulation:
  - Bit shifts, left and right shifts.
  - In MIPS its:
    - `sll` - shift left
    - `srl` - shift right
    - `and`, `andi` - logical and
    - `or`, `ori` - logical or
    - `nor` - logical not

# 2.7 Insturctions for Making Decisions

- Computers are distinguished from calculators based on their ability to make decisions.
- MIPS includes two decision making instructions, these are:
  - `beq register1, register2, L1` - This means go to the label L1 if the value in register 1 equals the value in register2.
  - `bne register1, register2, L1` - which will branch if the two are not equal
- Let's say we had the following C code, where `f`, `g`, `h`, `i` and `j` correspond to regsiters `$s0` to `$s4`
```c
if (i == j) {
  f = g + h;
} else {
  f = g - h;
}
```

```asm
  bne $s3, $s4, Else # go to Else if i != j
  add $s0, $s1, $s2 # f = g + h
  j Exit # go to Exit
  Else: sub $s0, $s1, $s2 # f = g - h
  Exit:
```
- What about loops?
- Let's assume i and k correspond to $s3 and $s5 and the base of the array save is in $s6
```c
while (save[i] == k) {
  i += 1;
}
```

- First step is load `save[i]` into a temporary register and to do this we need it's address. Before we can add i to the base of array `save`, we first have to multiply the index `i` by 4 due to byte addressing. We use `sll` to do this, because shifting left by 2 multiples by 2^2 (4).
```asm
Loop: sll $t1, $s3, 2
add $t1, $t1, $s6 # $t1 = address of save[i]
lw $t0, 0($t1) # temp reg $t0 = save[i]
bne $t0, $s5, Exit # go to Exit if save[i] != k
addi $s3, $s4, 1 # i = i + 1
j Loop # go to Loop
Exit:
```
- Such sequences of instructions that end in a branch are so fundamental to compiling that we call them a block, which is a sequence of instructions without branches. One of the first phases of compilation is breaking the program into blocks.
- If you want to check if a variable is less than another variable you can use `slt`, like `slt $t0, $s3, $s4 # $t0 = 1 if $s3 < $s4` which stands for "set on less than". There's also a sister operation called `slti` thats used like `slti $t0, $s2, 10 # $t0 = 1 if $s2 < 10`.
- MIPS compilers use `slt`, `slti`, `beq`, `bne` and `$zero` to create all relative conditions: equal, not equal, less than, less than or equal, greater than, greater than or equal.
- If you're working with unsigned integers, you can use `sltu` and `sltiu`.

# 2.8 Supporting Procedures in Computer Hardware
- Procedures (Functions) allow for easy code reuse.
- In order to do a function, the program must follow these six steps
1. Put parameters in a place where the procedure can access them,
2. Transfer control to the procedure
3. Acquire the storage resources needed for the procedure
4. Perform the desired task
5. Put the result value in a place where the calling program can access it.
6. Return control to the point of origin, since a procedure can be called from several points in a program.
- MIPS has has a few special purpose registers for this:
  - `$a0` - `$a3` which are four argument registers in which to pass parameters
  - `$v0` - `$v1` which are two value registers in which to return values
  - `$ra` one return address register to return to the point of origin
- MIPS includes an instruction just for procedures, it jumps to an address and simultaneously saves the address of the following instruction in register `$ra`. The jump-and-link instruction `jal` is used like `jal ProcedureAddress`
- The `jr` instruction jumps to the address stored in register `$ra`. Thus the calling program puts the parameters in `$a0` - `$a3` and uses `jal X` to jump to procedure X (the callee). The callee then performs the calculations, places the results in `$v0` and `$v1` and returns control to the caller using `jr $ra`.
- The return address gets stored in the **program counter**, this really should be called the instruction address register, but we call it this for historical reasons. The `jal` instruction saves PC + 4 in register `$ra` to link to the following instruction.

## Using more Registers
- If a compiler needs more registers for a procedure than the four argument and two return value registers, we have to restore any registers we used back to their previous status.
- This means we need to *spill* registers to memory, and the ideal place to do this is the stack - a last-in-first-out (LIFO) queue.
- A stack needs a pointer to the most recently allocated address in the stack to show where the next procedure should place the registers to be spilled or where old register values are found. The *stack pointer* is adjusted by one word for each register that is saved or restored, which is how it grows downwards.
- MIPS reserves register 29 for the stack pointer, calling it `$sp`. Placing data onto the stack is a *push* and removing data from the stack is a *pop*.
- Stacks "grow" from higher addresses to lower addresses, meaning that you push values onto the stack by subtracting from the stack pointer. Adding to the stack pointer shrinks the stack, popping values off the stack.

```c
int leaf_example (int g, int h, int i, int j) {
  int f;
  f = (g + h) - (i + j);
  return f;
}
```
- We start with the label of the procedure - line 1
- Then we save the registers used by the procedure, we need to save three registers so we create space on the stack for three registers, then push them onto the stack - lines 2 - 5
- Then we carry out the procedure. - lines 6 - 8
- We return the value of f by copying it to a return value register - line 9
- Before returning, we restore the three old values of the registers by popping them from the stack - lines 10 - 13
- The procedure ends with a jump register using the return address - line 14

```asm
1  | leaf_example:
2  | addi $sp, $sp, -12 # adjust stack to make room for 3 items
3  | sw $t1, 8($sp) # save register $t1 for use afterwards
4  | sw $t0, 4($sp) # save register $t0 for use afterwards
5  | sw $s0, 0($sp) # save register $s0 for use afterwards
6  | add $t0, $a0, $a1 # register $t0 contains g + h
7  | add $t1, $a2m $a3 # register $t1 contains i + j
8  | sub $s0, $t0, $t1 # f = $t0 - $t1 (g + h) - (i + j)
9  | add $v0, $s0, $zero # returns f ($v0 = $s0 + 0)
10 | lw $s0, 0($sp) # restore register $s0
11 | lw $t0, 4($sp) # restore register $t0
12 | lw $t1, 8($sp) # restore register $t1
13 | addi $sp, $sp, 12 # adjust stack to delete 3 items
14 | jr $ra # jump back to calling routine
```

- We can also take advantage of our temporary registers, where it's assumed that these do not get preserved by the called on a procedure call

## Nested Procedures
- Procedures that don't call others are called leaf procedures, and these aren't too common.
- If a function calls another one, we have to be careful because we can overwrite the values in our argument registers. A solution to this is to push all the registers that need to be preserved onto the stack. The stack pointer is adjusted to account for the number of registers placed on the stack. Upon return, registers are restored from memory and the stack pointer is readjusted.

```c
int fact (int n) {
  if (n < 1) {
    return 1;
  } else {
    return (n * fact(n - 1));
  }
}
```
- We start with the label of the procedure - line 1
- Then we save two registers, return address and $a0 on the stack - lines 2 - 4
- The first time `fact` is called, `sw` saves an address in the program called `fact`. Then we test whether `n` is less than 1, going to L1 if `n >= 1` - lines 5 - 6
- If n is less than 1, fact returns 1 by putting 1 into a value register - line 7
- It then pops the two saved values off the stack and jumps to the return address - lines 8 - 9
- If n is not less than 1, the argument n is decremented and then fact is called again with the decremented value - lines 10 - 11
- The next instruction is where fact returns. Now the old return address and old argument are restored, along with the stack pointer - lines 12 - 14
- Then the value register $v0 gets the product of old argument $a0 and the current value of the value register - line 15
- `fact` then jumps back to the return address - line 16
```asm
1  | fact:
2  | addi $sp, $sp, -8 # adjust stack for 2 items
3  | sw $ra, 4($sp) # save the return address
4  | sw $a0, 0($sp) # save the argument n
5  | slti $t0, $a0, 1 # test for n < 1
6  | beq $t0, $zero, L1 # if n >= 1, go to L1
7  | addi $v0, $zero, 1 # return 1
8  | addi $sp, $sp, 8 # pop 2 items off stack
9  | jr $ra # return to caller
10 | L1: addi $a0, $a0, -1 # n >= 1: argument gets (n - 1)
11 | jal fact # call fact with (n - 1)
12 | lw $a0, 0($sp) # return from jal: restore argument n
13 | lw $ra, 4($sp) # restore the return address
14 | addi $sp, $sp, 8 # adjust stack pointer to pop 2 items
15 | mul $v0, $a0, $v0 # return n * fact (n - 1)
16 | jr $ra
```

- A C variable is generally a location in storage, and its interpretation depends both on its *type* and *storage* class.
- C has two storage classes, automatic (local to a procedure) and static (existing across procedures).
- C variables declared outside all procedures are considered static, as well as any using the keyword `static`.
- To simplify access to static data, MIPS software reserves another register called the *global pointer*, `$gp`.

## Refresher on stack and heap
- Stack is a block of memory set aside as scratch space for a particular function or thread.
- The heap is set aside for dynamic allocation, and is how something like `malloc` works

## Allocating space for new data on the Stack
- The final complexity is that the stack is also used to store variables that are local to the procedure but don't fit in registers, such as local arrays or structures.
- The segment of the stack containing a procedure's saved registers and local variables is called a *procedure frame* or *activation record*.
- Some MIPS software uses a *frame pointer*, which is a value denoting the location of the saved registers and local variables for a given procedure.

## Allocating space for new data on the Heap
- In addition to automatic variables that are local to procedures, C programmers need space in memory for static variables and dynamic data structures.
- The stack starts in the high end of memory and grows down. The first part of the low end of memory is reserved, followed by the MIPS machine code. Above the code is the static data segment for variables and static variables.
- Although arrays tend to be fixed, linked lists and the like tend to grow and shrink. The segment for such data is called the *heap* and is placed next in memory. Allocating the stack and heap like this next to each other means they grow towards each other, allowing efficient memory use as the two segments grow and shrink.
- C allocates space on the heap with functions like `malloc` and `free`.

## Additional Notes
- If there are more than four params, MIPS convention is to place the extra params onto the stack just above the freame pointer.
- Frame pointer is convenient because all references to variables within a procedure use the same offset.

# 2.9 - Communicating with People
- Most computers use ASCII to represent characters cos its 8-bit. Of course, this has its problems but I don't know if it's going to be covered here...
- A series of instructions can extract a byte from a word, so load word and store word are sufficient for transferring bytes as well as words.
- MIPS gives us instructions to transfer bytes, `lb` and `sb`
```asm
lb $t0, 0($sp) # read byte from source
sb $t0, 0($gp) # write byte to destination
```
- Characters are normally combined into strings, which have a variable number of characters. There are three choices for representing a string:
1. The first position of the string is reserved to give the length of the string
2. An accompanying variable has the length of the string (like in a structure)
3. The last position of a string is indicated by a character used to mark the end of a string. This is the one C uses.

```c
void strcpy (char x[], char y[]) {
  int i;
  i = 0;
  while ((x[i] == y[i]) != '\0') {
    i += 1;
  }
}
```
- To init i to 0, the next instruction sets $s0 to 0 by adding 0 to 0 and placing that sum in $s0 - line 4
- Beginning of loop, address of y[i] is formed by adding i to y[] - line 5
- Note we don't have to multiply i by 4 since y is an array of bytes, and not of words.
- To load the character in y[i], we use load byte unsigned which puts the character into `$t2` - line 6
- A similar address calculation puts the address of x[i] in $t3 and then the character in $t2 is stored at that address. - line 7 and 8
- Next, we exit the loop if the character was 0, meaning if we're at the last character of the string - line 9
- If not, we increment i and loop back - lines 10 and 11
- If we don't loop back, it was the last character of the string and we restore $s0 and the stack pointer and then return - lines 12 - 14
- String copies usually use pointers instead of arrays in C to avoid the operations on i in the code above
```asm
1  | strcpy:
2  |   addi $sp, $sp, -4 # adjust stack for 1 more item
3  |   sw $s0, 0($sp) # save $s0
4  |   add $s0, $zero, $zero # i = 0 + 0
5  |   L1: add $t1, $s0, $a1 # address of y[i] in $t1
6  |   lbu $t2, 0($t1) # $t2 = y[i]
7  |   add $t3, $s0, $a0 # address of x[i] in $t3
8  |   sb $t2, 09$t3) # x[i] = y[i]
9  |   beq $t2, $zero, L2 # if y[i] == 0, go to L2
10 |   addi $s0, $s0, 1 # i = i + 1
11 |   L2: lw $s0, 0($sp) # y[i] == 0: end of string
12 |   addi $sp, $sp, 4 # pop 1 wor off the stack
13 |   jr $ra # return
```
- Since the above procedure above is a leaf procedure, the compiler could allocate i to a temporary register to avoid saving and restoring $s0. We can thus think of the $t registers as being for temporaries, but also for registers that the callee can use whenever convenient
- When a compiler finds a leaf procedure, it exhausts all temporary registers before using registers that it has to save.

## Characters and Strings in Java
- Java uses Unicode, which uses 16 bits to represent a character.
- MIPS has explicit instructions to load and store 16 bit quantities, called halfwords. `lh`, loads a half word and places it in the rightmost 16 bits of a register
- This only works on signed integers, so you can use `lhu` to load unsigned half words. `sh` store half, takes a halfword from the rightmost 16 bits and writes it to memory.
```asm
lhu $t0, 0($sp) # read halfword (16 bits) from source
sh $t0, 0($gp) # write halfword (16 bits) to destination
```

# 2.10 MIPS Addressing for 32-bit Immediates and Addresses (p111 - 113)
- Although keeping all MIPS instructions 32 bits long simplifies the hardware, its sometimes convenient to have a 32 bit constant or 32 bit address.

## 32-Bit Immediate Operands
- Although constants are frequently short and fit into 16-bit field, sometimes they're bigger. The MIPS instruction *load upper immediate* `lui` sets the upper 16 bits of a constant in a register, allowing a subsequent instruction to specify the lower 16 bits of the constant.

- In order to load a MIPS assembly code to load this 32-bit constant into register $s0 we do this:
`0000 0000 0011 1101 0000 1001 0000 0000`
- First we load the upper 16 bits, using `lui`. This puts 61 in binary into the register $s0 which is 16
- Then we insert the lower 16 bits, which is 2304
```asm
lui $s0, 61 # 61 decimal = 000... in binary
ori $s0, $s0, 2304 # 2304 decimal
```
- Either the compiler or assembler must break large constants into pieces and then reassemble them into a register. As you might expect, immediate's size restriction may be a problem for memory addresses in loads and stores as well as for constants
- Basically, creating 32 bit constants requires care. The instruction `addi` copies the leftmost bit of the 16bit field of the instruction into the upper 16bits of a word. *Logical or immediate* loads 0s into the upper 16 bits, and hence is used in conjunction with `lui` to create 32 bit constants.
