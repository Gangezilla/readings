2a) `$sp` refers to the stack pointer, which is a variable that holds the current place on the stack that allows you to load data into it. You subtract from `$sp` before storing data in the stack, and you add to `$sp` after restoring.
b) The registers that need to be saved and restored after using `jr` (jump register) are any `$s*` registers, as these are assumed to be safe. Any `$t*` registers don't need to be restored as they're assumed to be temporary.
c) $ra and all $t*, $a* and $v* registers if the values they contain are needed after the function call.
d) We pass arguments into functions by using the $a0 - $a3 registers. These are the argument registers and are specifically reserved for this purpose.
e) If we have more than four arguments for a function we should either simplify the function, or use the stack to store additional arguments.
f) We return values out of functions by using the $v0 and $v1 return value registers.

N/A, Caller, Caller, Caller, Callee, N/A, Caller

4a) Not too sure on whats happening in the middle here...

```asm
addiu $sp, $sp, -4 # adjust stack for 1 item
lw $t0, 0($a0) # put first argument value into temp register 0
sw $t0, 0($sp) # put temp register into stack
lw $t0, 0($a1) # put second argument value into temp register 1
sw $t0, 0($a0) #
lw $t0, 0($sp)
sw $t0, 0($a1)
addiu $sp, $sp, 4 # restore stack
jr $ra # exit function call
```

4b)
```asm
Start: add $s1 $0 $0 # set sum to 0
Loop: beq $s0, $0 Ret # if $s0 (N) is 0, call Ret, otherwise fall through and loop
add $s1, $s1, $s0 # add N to sum
addiu $s0, $s0, -1
j Loop
Ret: addiu $v0, $s1, 0 # put sum into out value register
j Done # jump to Done
Done: jr $ra # jump to value in $ra
```

4c) Add a before and after to reserve and clear space on the stack in order to store all the necessary variables.

5a) The Stored Program concept is the idea that instructions are the same as data, so we should treat them as such. This means we can write programs that manipulate other programs, as they're all stored somewhere in memory.
b) The assembler passes through the code twice, the first time to find all the label addresses and another to convert all instructions while resolving any forward references using the collected label addresses.
c) There are several different parts of the object files output by the Assembler.
- Header: Size and position of other parts
- Text: The machine code
- Data: Binary representation of any data in the source file
- Relocation Table: Identifies lines of code that need to be "handled" by Linker
- Symbol Table: List of the files labels and data that can be referenced
- Debugging Information: Additional information for debuggers
d) The assembler resolves relative addressing, and the linker resolves absolute addressing.
e) Assemblr uses the $at register
f) Reduced Instruction Set Computing, which is the idea that there's a reduced number of instructions that can be composed to make complex programs. This leads to a larger number of instructions but is easier to comprehend. Pseudoinstructions are more complex instructions intended to make assembly progrmaming easier for the coder. These are converted by the assembler.
