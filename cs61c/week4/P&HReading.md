# 2.5 - Representing Instructions in the Computer
- Instructions are kept in the computer as a series of high and low electronic signals and may be represented as numbers. Each piece of an instruction can be considered as an individual number and placing these side by side forms the instruction.
- Since registers are referred to in instructions, there must be a convention to map register names to numbers.
- In MIPS, registers $s0 to $s7 map to registers 16 - 23, $t0 - $t7 maps to 8 - 15.
- An instruction like `add $t0, $s1, $s2` is represented in decimal as `0 17 18 8 0 32`. Each of these segments is a field. The first and last fields together tell MIPS that this instruction performs addition. The second field gives the number of the register of the first source operand, and the third gives the other one. The fourth field is the register that will receive the sum, and the fifth field is unused so is set to 0. In binary, this instruction is exactly 32 bits.
- The layout of the instruction is called the **instruction format**. All the bits above add up to 32 bits, like all MIPS instructions.
- We call these bits **machine language** to differentiate it from assembly language. We convert these to hex to make it easier to read and interpret.
- We convert between the two by just, like, looking at each individual part of it and converting it.
- MIPS fields are all given names to make them easier to discuss.
**Design Principle 3:** Good design demands compromises
- In order to keep all the instructions 32 bits, some of the instructions use different bit amounts for their individual fields.

- Today's computers are built on two key principles:
1. Instructions are represented as numbers
2. Programs are stored in memory to be read of written, just like data.
- These principles lead to the *stored-program* concept, meaning that a computer's memory contains the source code for an editor, the corresponding compiled machine code, the text that the compiled program is using, and even the compiler that generated the machine code.

# 2.10 - MIPS Addressing for 32-bit Immediates and Addresses
- Keeping all MIPS instructions 32 bits long simplifies the hardware, we sometimes need a 32 bit constant or address.
- Although constants are frequently short and fit into the 16-bit field, sometimes they're bigger.

## Loading a 32 bit constant
If we have a 32 bit constant, and we want to get it into a register  `$s0`, there's a few steps we'd take.
- First we'd load the upper 16 bits into the register like so:
`lui $s0, 61 # 61 decimal = first 16 bits of the binary number`
- Next, we insert the lower 16 bits:
`ori $s0, $s0, 2304`
- This puts the correct value into the register.

## Addressing in Branches and Jumps
- The MIPS jump instructions have the simplest addresing. They use the final MIPS instuction format, called the *J-Type*, which consists of 6 bits for the operation field and the rest of the bits for the address field.
- You can specify a register to be added to a branch address to allow the program to be as large as 2^32 and still be able to use conditional branches.
- This form of branch addressing is called *PC-relative addressing*, it's convenient for the hardware to increment the PC early to point to the next instruction. Hence, the MIPS address is relative to the address of the following instruction, as opposed to the current instruction.

# 2.12 - Translating and starting a Program
Compiler => Assembler => Linker => Loader
## Compiler
- The compiler transforms the C program into an assembly language program. In the 70s lots of stuff was written in assembly because it was faster, but now because of better compilers and more memory in computers, compilers are nearly as good at or sometimes better than assembly language experts.
## Assembler
- Since assembly is an interface to higher level software, the assembler can also treat common variations of machine language instructions as if they were instructions in their own right. The hardware doesn't need to implement them, but their appearance in assembly makes translation easier, these are called *pseudoinstructions*.

# A.1 - A.4
