# Compiler, Assembler, Linker, Loader (CALL) - 2015-02-12

## Language Execution Contiuum

- Contiuum of code represented
- High level languages are easy to program, but inefficient to interpret. Low elvel languages are difficult to program, but efficient to interpret
- Language traslation gives us another option
- In general, we interpret a high level language when efficiency is not critical, and translate to a lower level language to up performance

## Interpretion vs Translation

- Interpreter directly executes a program in the source language
- Translation is more efficient, looks at a program once in source language and converts it to a lower level language.

## Interpretation

- A language like Python is interpreted, but what happens under the hood, is that a Python script is just data to the Python interpreter which looks at your code and figures out what you have to do. Very quick to write a script because of this. But becaause of all this interpretation it ends up like 100x faster than a compiled program.
- Sometimes it's useful to interpret very low level programs like machine code, something like MARS which is a MIPS interpreter because we aren't using a MIPS processor.
- Another interesting case is when a company changes instruction sets. Like, when Apple changed the Mac from PowerPC to x86. This could require all programs to be re-translated from high level language, or lets executables contain old and/or new machine code, interpreting old code in software if necessary (emulation).
- With the PowerPC machines they shipped an interpreter in software that allowed the computer to pretend it was the old architecture.
- This means that some programs have x86 and PowerPC versions.
- This is super costly, but Apple being a big smart company has all their software running on various processor architectures

## Interpretion vs Translation

- Interpreters are very easy to write, but they're a lot slower. Translated/compiled code is almost always more efficient and therefore higher performance.
- Translation/compilation helps "hide" the program "source" from the users too.

## Steps in compiling a C program

- C program -> compiler -> produces an assembly program -> assembler -> produces an object file -> linker -> takes all these different object files and makes one executable -> loader -> takes that executable, pops it in memory and runs it

## Compiler

- Input: High level language code (foo.c)
- Output: Assembly Language Code (foo.s for MIPS)
- Output may contain pseudoinstructions. Pseudoinstructions are instructions the assembler understands, but not in machine, like
  `move $s1, $s2 => add $s1, S2, $zero`. A move instruction doesn't exist in MIPS but it's a lot clearer.

## Assembler

- Input: Assembly language
- Output: Object code (binary)
- This is only for one module in your program. A .o file you produce is only a partial part. As well as object code, it creates information tables that are needed to put everything together.
- Assembler reads assembly and in that there's directives, which are instructions to the assembler for what to do with the code. The assembler reads this, and expands pseudoinstructions into real instructions. It produces machine language, and object file and info on how to put all this together.
- Some assembler directives are a way to give directions to the assembler, but they don't produce machine instructions.

## Pseudoinstruction Replacement

- Asm. treats convenient variations of machine language instructions as if real instructions. There's basically a number of instructions that are one line pseudo, and get turned into multi line real instructions. There's some examples in the lectures if you're keen at some point...

## Integer Multiplication

- m bits x n bits = m + n bit product
- 32bits x 32bits could be a 64 bit number
- In MIPS we multiply registers by putting the numbers in two special registers, `hi` and `lo`, where the high 32 bits live in the high register and the low 32 bits live in the low register.
- `mfhi` and `mflo` to get these numbers.

## Integer Division

- Similar.
- MIPS divide instruction figures out the remainder and quotient and puts them in hi and lo.
- remainder goes in `hi` and quotient goes in `lo`.

## Producing Machine Language

- Simple case: Arithmetic, Logical, SHifts and so on. All necessary info is within the instruction already
- Branches are different because they're PC relative. I don't know till I expand my instructions what they are
- You have this forward reference problem. Branch instructions can reger to labels that are "forward" in the program.
- This is solved by taking 2 passes over the program. First pass reads through and finds all the labels, second pass use label positions to generate code.
- Jumps (j and jal) require absolute addresses. So, forward or not, still can't generate machine instruction without knowing the position of instructions.
- Static data, requires full 32 bit address of the data.
- These can't be determined yet, so we create two tables.

## Symbol table

- List of "items" in this file that may be used by other files.

## Relocation table

- List of "items" this file needs the address of later.
- Internal and external, as well as any piece of data in the static section. I can call a function here or in another file too

## Object FIle Format

- Not just a string of 1s and 0s. Several parts
- Object file header - how big the segments are
- text segment holding machine code
- data segment holds initialised data of this file
- relocation info - what lines need to be fixed later
- symbol table - all labels and interesting points for other things to use. What other files need to know to access this file.
- Lots of debugging information too.
- A standard format in Unix is something like ELF
- This is all you need to get an executable.

## Linker

- Takes all object files and builds one file. Brings in standard libraries, rewrites very little of the code
- Input: Object code files and information tables
- Output: Executable Code
- Combines several object (.o) files into a single executable ("linking")
- Enables incremental compilation. If I change one C file I just need to redo that one files object files and then you're good to go again.
- Changes to one file don't require recompilation of whole program. Compiling an OS these days would take like 10 hours lol
- A linker takes multiple object files with it's text data and info, and the linker uses all of this to put the text together and the data together.
- Step 1: Take text and put together. Step 2: Take data segement put together and concat into end of text segments. Step 3: Resolve references. Go through relocation table and handle everything.

## Four Types of Addresses

- PC-relative Addressing (beq, bne) - never relocate. Wherever the final code ends up, itll always be + or - x instructions
- Absolute Function Address (j, jal), External Function Reference (usually jal), Static Data Reference (lui, ori etc) - Always relocate. With these you have to figure out where something lives.

## Resolving References

- Linker assumes first word of first text segment is at a particular address and stacks the text sections from object files on top of each other.
- Linker knows length of each text and data segment, ordering of text and data segments
- Linker calculates absolute address of each label to be jumped to and each piece of data being referenced.
- To resolve references, search for reference in all "user" symbol tables. If not found, search library files, once absolute address is determined, fill in machine code appropriately. Linker outputs one big fat executable which is often `a.out`

## Loader

- Input: Executable Code
- Output: program is run
- Executable files are stored on disk
- In reality, loader is the OS.
- On disk, you've got this data file describing the program. The loader creates this running image and figure out how much space it needs in virtual memory. Basically create an address space for it to run in, copy into memory text from the data file. Initialise the stack by pushing on the arguments. Copies instructions, sets up registers. Then we jump to the start up routine and starts going. When it exits it jumps back into the OS functionality, deallocates the space etc.

## Example C => Asm => Obj => Exe => Run

- Header file tells the C compiler what to expect is coming in from the program. It's a way of linking this C compilation to all the other bits in the program without having to go look everywhere.
- First thing the ASM looks like is a `.text` saying this is all text. After that is a `.align 2` which says to align to 4 bytes of memory, telling the assembler that everything has to start on a 4 byte boundary. After that is `.globl main` which says when you assemble this put it in the other files so everything else knows where to look
