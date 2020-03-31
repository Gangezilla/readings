# Intro to MIPS

- Last lecture, started looking at high level languages like C. Next few lectures we'll be looking at what the compiler creates as an intermediate languatge thast super close to the hardware.
- Instructions from a compiler map 1-1 to a string of bits that a computer understands, an assembler is what does this for us.
- Basic job of a CPU: execute lots of instructions. Instructions are the primitive operations that the CPU may execute.
- An instruction is a thing that a piece of hardware can do very quickly and very efficiently.
- A collection of instructions, like a vocabulary, is called the Instruction Set Architecture (ISA). These are all different for each different CPU.

## ISAs

- Early trend was to have instructions on CPUs do elaborate operations, like multiplying polynomials. This is a complex task that could be broken down quite a bit.

- RISC philosophy, Reduced Instruction Set Computing. Recognise small patterns that occur very frequently, and optimise the hardware to do this really quickly.
- Let software do complex operations by composing simpler ones. Lets you make bigger and faster things too.

## MIPS

- One of the first semiconductor companies that built a commercial RISC architecture. In this class we'll look at MIPS for it's simplicity. It's assembly is quite easy to learn.
- We're using MIPS cos it's quite simple and elegant. Used quite regularly in embedded apps, x86 is a bit too complicated and is used mostly in PCs.
- Latest ARM 64 bit is pivoting towards a MIPS instruction style.

## Assembly Variables: Registers

- Our variables are things that exist physically in hardware, registers. There's only a limited number of them.
- We only have 32 registers to work with. Everything we do has to be done within that little sandbox. This is so that we can keep the hardware simple!
- Since registers are directly in hardware, they're super fast, but there are a predetermined number of them.
- Each MIPS register is 32 bits wide, and a group of 32 bits is called a _word_ in MIPS.
- Each register can be referred to by number, or by name.
  - By number is $0, $1, \$31...
  - $16 - $23 are saved variable registries, $s0 - $s7 which is kinda like a variable in a C program. So if we had a variable in C, we'd put it here.
  - $8 - $15 we call $t0 - $t7 for temporary variables. It's something that's an intermediate computation that I only need now but not later on.
  - We'll go through the others later on.

## C, Java variables vs registers

- In C (and other high level langs) variables are declared first and given a type.
- In Assembler, all bets are off. Registers have no type, an operation determines how register contents are treated.

## Addition and Subtraction of Integers

- In MIPS this looks like:
  Adding:

```c
  add $s0, $s1, $s2
  a = b + c
```

Subtracting:

```c
  sub $s3, $s4, $s5
  d = e -f
```

What about `a = b + c + d - e;`?

```asm
  add $t0, $s1, $s2 # temp0 = b + c
  add $t0, $t0, $s3 # temp + d
  sub $s0, $t0, $s4 # a = temp -e
```

- A single line of C may break up into several lines of MIPS. We use temporary registers often because we don't want to modify the variable registers `$s`
- Use lots of comments because assembly is fucked

## Immediates

- Immediates are numerical constants. They get embedded in the instructions. They appear often in code, so there's special instructions for them.
- You can do `addi $s0, $s1, -10` which is equivalent to `f = g - 10`.
- That -10 becomes part of the string of bits that are under the hood. This allows you to write this number here directly, without having to go and get it from memory.
- Syntax similar to `add` instruction, except that the last argument is a number instead of a register.
- Zero is so special it has it's own register, `$zero`. `add $s0, $s1, $zero` is equivalent to `f = g`

## Overflow in Arithmetic

- Reminder: Overflow occurs when there's a mistake in arithmetic due to the limited precision in computers.
- When overflow occurs the computer should react in some way, usually an error or something.
- In MIPS, we handle this a bit differently. There are 2 kinds of arithmetic instructions, ones that detect overflow and ones that don't.
- `add`, `addi`, and `sub` detect overflow
- `addu`, `addiu`, `subu` does not detect overflow, and indicates to MIPS that you're using unsigned variables, which you'd usually use for addresses and not arithmetic

## Data Transfer

- When we're retrieving data we
- Write data to memory, we read data from memory to the CPU.
- _Store_ means store to memory from the processor, and load means to load from memory to the processor. Once I'm done working on it, I _store_ it back in memory.
- Program will be big, so we'll probably want to store it in memory as well

## Memory Addresses are in Bytes

- A byte is a chunk of information. Lots of data is smaller than 32 bits, but rarely smaller than 8 bits - works fine if everything is a multiple of 8 bits.
- An 8 bit chunk is called a byte. Because we have 32 bit registers, instead of fetching a byte at a time, we usually go and fetch a whole word (1 word = 4 bytes or 32 bits)
- Memory addresses are really in bytes, not words. To fetch a word, I have to increment my memory address in multiples of 4.
- Word address is same as address of leftmost byte in big-endian, and it looks something like this.
  | 12 | 13 | 14 | 15
  | 8 | 9 | 10 | 11
  | 4 | 5 | 6 | 7
  | 0 | 1 | 2 | 3

## Transfer from memory to register

- We want to _load_ our data.
- We use `lw` or Load Word

```c
int A[100];
g = h + A[3];
```

```asm
lw $t0, 12($s3) # Temp reg $t0 gets A[3]
add $s1, $s2, $t0 # g = h + A[3]
```

We set an address, and then we set an offset of 12. We add 12 because it's the size of 3 words. To go from A[0] to A[3], we have to increment the base by 3 words, and each word is 32 bits, or 4 bytes. So we increment by 4 x 3, 12.

- We set the offset **in BYTES**
- Offset must be a constant known at compile time

## Transfer from Register to Memory

```c
int A[100];
A[10] = h + A[3];
```

```asm
lw $t0, 12($s3) # Temp reg $t0 gets A[3]
add $t0, $s2, $t0 # Temp reg $t0 gets h + A[3]
sw $t0, 40($s3) # A[10] = h + A[3]
```

- \$s3 is a register that contains a pointer to the base of the array.
- $s3 + 12 and $s3 + 40 must be a multiple of 4. If it's not I get byte misaligned meaning I get some bytes from one word and then a ferw from another. Whenever you use `sw` or `lw`, it has to be a multiple of 4.

## Loading and Storing bytes

- In addition to loading and storing a word, you've also got `lb` and `sb` to load and store a byte. The address can be whatever, because this is the smallest possible unit.
- If you do this, it loads it into the lowermost byte in the register (cos you've gotten 8 bits in a 32bit register)
- It takes the sign bit and "sign-extends" it, meaning it gets copied aaaaaall the way to the end of the register.

## Speed of Registers vs Memory

Using the registers are like 100 - 500 times faster than going to memory, so we want to minimise the number of times we go to memory.

## MIPS Logical Operations

- Useful to operate on fields of bits within a word
- Operations to pack/unpack bits into words, logical operations to do bit by bit operations. You often create like a mask and then do operations on the appropriate bits.
- `&`, `|`, `~`, `<<`, and `>>`
- `sll` is shift left. This is the same arithmetic effect as multiplying a number by 4.
- `srl` is shift right.

## Computer Decision Making

- In MIPS for an if statement, we have a few ways of doing this
  `beq register1, register2, L1` which is 'branch if equivalent' and if it is equivalent, it'll jump to whatever's in L1. In front of every MIPS instruction, you can put a label in front of it. I guess it's like a jump statement in 8080. It's like a goto statement, really bad in higher level langs, but necessary in MIPS.
- Other instruction, `bne`, branch if not equal
- Branches are a way of changing the control flow.
- Conditional branches are where we jump somewhere or not, based upon some condition.
- Unconditional branch, where we _always_ want to jump, `j`. Like, when we're done in a function we want to jump out and go back to where we were.
