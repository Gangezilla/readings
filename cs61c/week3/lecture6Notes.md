# MIPS, MIPS Functions - 2015-02-05

- Assembly is the human readable version of machine code, machine code is just 1's and 0's that live in memory, it's the lowest level.
- Assembly is a slightly easier way to read machine code.
- MIPS is a very rigid format. 1 operation, 2 source operands, 1 destination.
  - Operations to do arithmetic, move data to and from registers/to and from memory, to do decision/control flow.
- In MIPS every instruction is 32 bits, makes it easy to fetch from memory. Every 4 bytes the machine just steps through and does something.
- The assembler takes binary code and converts it into machine code. Assembler source files end in `.s`

## Executing a Program

- The PC (program counter) is an internal register inside processor holding byte address of next instruction to be executed.
- Instruction is fetched from memory, then that instruction is executed and the program counter gets updated.

## Computer Decision Making

- Computers can make decisions, or branch based off some value. In high level that's an if statement.
  - `beq register1, register2, l1` if the value in reg1 == reg2, go to this label.
  - L1 is a label in an assembly file, it refers to a particular spot in the file
  - If the branch is false, fall through to the next instruction.
- Conditional Branch - change control flow depending on outcome of comparison.
  - Branch if equal (beq) or branch if not equal (bne)
- Unconditional branch - always branch (j)

## Example if statement

- Assumptions: f -> $s0, g -> $s1, h -> $s2, i -> $s3, j -> \$s4

```c
  if (i == j) {
    f = g + h;
  }
```

```asm
bne $s3, $s4, Exit
add $s0, $s1, $s2
```

- When it hits `Exit`, you can specify some label in the program which is text followed by a colon.
- To make it easier for the human you can just use symbolic labels like this.
- The condition in the high level language, you might need to negate it here.
- You could do it with a label but it's more complicated, so you do this.
- This kind of optimisation is something the C compiler is really good at doing. The compiler isn't perfect, but it figures out the most efficient way to do this.

```c
if (i == j) {
  f = g + h;
} else {
  f = g - h;
}
```

```asm
bne $s3, $s4, Else
add $s0, $s1, $s2
j Exit
Else: sub $s0, $s1, $s2
Exit:
```

- If the condition is met on line 1, it falls through to the add on line 2. After the add it then unconditionally jumps to exit. If it doesn't meet the condition it jumps to the Else label.
- Labels are just stored in the text file. The assembler sees where they are, and converts them to offsets in the branch instruction. The MIPS assembler sees how many +- bytes are there to get to this label.

## Inequalities in MIPS

- If you're checking if a value is less than or greater than, MIPS has an instruction that's `slt` or 'Set on Less Than'.
  `slt reg1, reg2, reg3` means

```c
if (reg2 < reg3) {
  reg1 = 1;
} else {
  reg1 = 0;
}
```

`if (g < h) goto Less;` in asm becomes

```asm
slt $t0, $s0, $s1
bne $t0, $zero, Less
```

- Something in high level language that looks like one statement becomes multiple.
- Architects argue about whether something should be one or multiple instructions. How granular do you go.
- Register `$zero` always contains the value 0, so `bne` and `beq` often use it for comparison after an `slt` instruction.
- `sltu` treats registers as unsigned. Useful for range comparisons. In the registers you just have bit patterns

## Immediates in Inequalities

- `slti` an immediate version of `slt` to test against constants
- `slti $t0, $s0, 1` sets $t0 if $s0 is less than 1.

## Six Fundamental Steps in Calling a Function

- The idea of a subroutine was from this guy called Wheeler working on the very first stored program computer, and invented the subroutine. Originally called the Wheeler jump because you could go to one function then come back. Before that you would just copy it every time you needed it. Neat.
- It's amazing that this field is so young, we know the people who invented everything.

1. Put parameters in a place where function can access them.
2. Transfer control to function
3. Acquire (local) storage resources needed for function. They get allocated to the stack
4. Perform desired task of the function.
5. Put result value in a place where calling code can access it and restore any registers you used.
6. Return control to point of origin, since a function can be called from several points in a program

- These are the steps your high level function needs for this to work.

## MIPS Function Call Conventions

- Registers faster than memory, so use them where possible over memory.
- $a0 - $a3 are our four _argument_ registers to pass parameters
- $v0 - $v1 are our two _value_ registers to return values.
- \$ra is our one _return address_ register to return to the point of origin.

- In MIPS, all instructions are 4 bytes and are stored sequentially in memory.

```c
...sum(a, b);
int sum (int x, int y) {
  return x + y;
}
```

```asm
  1000 add $a0, $s0, $zero # x = a This is basically copying a value
  1004 add $a1, $s1, $zero # y = b
  1008 addi $ra, $zero, 1016 # $ra = 1016 storing the place we want to come back to in ra
  1012 j sum # jump to sum
  1016 ...
  ...
  2000 sum: add $v0, $a0, $a1
  2004 jr $ra # new instruction
```

- In here we code the absolute return address, MIPS has this other instruction called `jal` or Jump and Link.
- Before:

```asm
1008 addi $ra, $zero, 1016
1012 j sum
```

After:

```asm
1008 jal sum $ra = 1012, goto sum
```

- It's implicit because they wanted to save some bits, also makes the common case really fast. Also means we don't have to know where code is in memory with `jal`, which is easier but also means if shit moves around you're protected.
- Invoke function: `jal`, link to form an address that points to a calling site, then jumps to address and simultaneously saves the address.
- Return from function: jump register instruction `jr` unconditional jump to address specified in register`jr $ra`
- Calling program (caller) puts parameters into registers $a0 - $a3, and uses jal X to invoke (callee) at address X
- Must have resigter in computer with address of currently executing instruction
  - Instead of Instruction Address Register, it's historically called the PC
  - You have to put the return address to one past where it was called, otherwise you'll never be able to get out.

## Where are old register values saved to restore them after a function call?

- Everyone wants to use registers, but we've only got a finite number of them. We need some kind of convention across our functions on how to share registers.
- Need a place to save old values before call function, restore them when return and delete.
- Ideally this is done in the _stack_, last-in-first-out queue. Push: placing data onto stack, pop: removing data from stack.
- Stack in memory, so need register to point to it.
- \$sp is the stack pointer in MIPS
- Convetion is to grow from high to low addresses. Push decrements $sp, Pop increments $sp

## Stack Before, During, After Function

- Need to save old values of $s0, and $t0. So you can push values onto the stack and then pop them off later on.
- Firstly you allocate space on the stack by decrementing the stack pointer

```asm
addi $sp, $sp, - 8 # adjust stack for 2 items
sw $t0, 4($sp) # save $t0 for use afterwards
sw $s0, 0($sp)
...
lw $s0, 0($sp) # restore register $s0
lw $t0, 4($sp) # restore register $t0
addi $sp, $sp, 8 # adjust stack to delete 2 items
jr $ra # jump back to calling routine.
```

## What if a function calls a function? Recursive Function calls?

- One thing to think about, argument registers, I'm reading them coming in, but if I'm calling another function I have to think about hwo I store them.

## Nested Procedures

- You ahve to save this stuff to memory if you don't want it to get stomped on.

```c
int sumSquare(int x, int y) {
  return mult(x, x) + y;
}
```

- When I call sumSquare, I give it a return address that I want it to come back to, so I have to save my original return address.
- General idea is you save all this stuff on the stack
- In C, you've got a few memory areas: Static is variables declared once per program, Heap: Variables declared dynamically by malloc, Stack: Space to be used by procedure during execution; this is where we can save stuff.
- You call functions a lot. Compiler writers spend a lot of time thinking about this. To reduce expensive loads and stores from spilling and restoring registers, MIPS divides registers into two categories.
  - You've got registers you have to preserve across function calls. Convention says some registers need to be restored back to as they should be, otherwise you're in a world of hurt.
  - And registers that aren't preserved. Temporary registers don't need to be set back to how they used to be.

## Allocating Space

- C has two storage calsses: automatic (variables are local to function and discarded when function exits) and static (variables exist across exits from and entries to procedures)
- Use stack for automatic (local) variables that don't fit in registers
- Procedure frame or activation record: segment of stack with saved registers and local variables.
