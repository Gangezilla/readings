# Single Cycle CPU Datapath & Control Part 1 - 2015-02-19

## Review

- Timing constraints for finite state machines
- Use muxes to select among inputs
- ALU can be implemented using a mux

## How to design adder/subtractor

- Any combinational circuit, you can describe it as a truth table. But, with something with mayn many inputs it's a huuuge truth table and it's too complex. When you're designing something like this, you break it down into smaller pieces and then add it back up.
- With a 32 bit adder, we look at 2 bits, which lets us have 4 rows instead of 2 ^ 64. For numbers like 2, you have a carry bit. You do the same in binary, if you add 2 bits and get a sum that won't fit in 1 bit. The LSB is the easy bit cos there's no carry in that position. You propagate the carry up to the higher bits.
- So we then build up with a few more bits, with 3 inputs we get an 8 row input table now. it ends up being a combination of different logic gates to end up making the middle bit of the adder.
- Half adder and a full adder

## N 1-bit adder => 1 N-bit adder

- To make a large adder you just string them all together with the carrys flowing through from one into the next one. So they're all chained together like this. Problem is if all your values get through at the same time, then your values will arrive at different times and out of order.

## Subtractor

- Because we're using two's complement, (which is inverting the bits and adding 1 to go pos/neg). The way we do subtraction is to take a number and add another number and negate. So we do 8 + -b instead of 8 - b.
- XOR gate is interesting cos it acts as a conditional inverter.
- We reuse the adder functionality with a layer of XOR gates to change its behaviour.

## Components of a Computer

- Processor, split into two parts, control and datapath. datapath is where the PC, ALU and registers live.
- Processor connects to memory, where all your data lives. Full of bytes
- I/O to read from keyboard and output to monitor etc.

## The CPU

- Processor (CPU): the active part of the computer. We break this down into the datapath (the brawn), and the control (the brain).

## Five stages of instruction execution

- Instruction Fetch
- Instruction Decode
- ALU
- Memory Access
- Register Write

## 1/5 Instruction Fetch

- There's a wide variety of MIPS instructions. Stored program computer, instructions are stored in memory. The computer has to read instructions into memory. Taking the current value of the PC that represents an address, getting the bits. It's also where we increment the PC (PC = PC + 4) to point to the next instruction.
- gets the address, 32 wires, decodes the 32 bits to figure out which cells are stored in, then pushes them back over another 32 wires. memory is kind of like a big block where you specify the 32 blocks you want, and it returns the ones youre after.

## 2/5 Instruction Decode

- Upon fetching the instruction, circuitry looks across these and figures out what to do. The opcode tells you what format to use, and what the remaining fields are.
- First read opcode, second read in data from all necessary registers.
- Diff instructions read diff numbers of registers

## 3/5 ALU

- The real work is done here. Arithmetic, shifting, logic and comparisons.
- What about loads and stores? The address we're accessing in memory.
- Only need one adder

## 4/5 Memory Access

- Actually only the load and store instructions do anything during this stage, the others remain idle. Let's assume our memory is mad fast for now, but later we talk caches.

## 5/5 Register Write

- Do an add, read the registers in decode stage, most instructions write the result of some computation into a register.
- Examples: arithmetic, logical, shifts, loads, slt.
- What about stores, branches, jumps? They read a register, change a condition... they don't change registers

## Stages of execution on datapath

- Nearly all machines have instructions and data together.
- Why 5 stages? MIPS and other RISC architectures have around this number of steps. Only one instruction uses five stages, which is load. Everything else uses a varying number of those steps.

## Datapath and Control

- Datapath designed to support data transfers required by instructions. Controller causes correct transfer to happen. What's interesting is lots of CPU designers get excited about designing the datapath, it's pretty fun to design. It's the bulk of the logic gates. Fun and really hard to design. Control piece of hardware is the hardest part of hardware.

## Processor Design

- Step 1: Analyze instruction set to determine datapath requirements. Meaning of each instruction, datapath must include storage element for ISA registers, datapath must support each register transfer.
- Step 2: Select set of datapath components & establish clock methodology. Easy these days
- 3: assemble datapath
- 4: analyze implementation of each instruction

## MIPS instruction format

- All MIPS instructions are 32 bits long. 3 formats, R, I, and J-Type. They've all got different sections which vary in length.

## Register Transfer Level (RTL)

- Making sure the hardware does exactly what was designed. We use this thing called RTL which gives the meaning of the instructions. All start by fetching the instructions itself.

## Step 1: Requirements of the instruction set.

- Memory (MEM)
- Registers
- Program Counter (PC)
- Extender (sign/zero extend)
- Add/Sub/OR/etc unit for operation on register(s) or extended immediate (ALU).

## Step 2: Components of datapath

- Combinational elements
- storage elements + clocking methodology
- Building blocks

## Storage Element - Idealized Memory

- Magic memory: address input that tells you what you're keen on accessing, data output for when you do a read or load so you can get the value
- Also has a write enable which tells it if it's reading or writing right now. Tells what you want to do to memory right now.
- Imagine memory being whole set of registers, which one you want to access. New set of registers with value you want to write to.
- Lots of registers, at clock edge one of them is read or written to.
- We view it as combinational, whatever address comes in at some point the.
- Only do the write on the next rising clock edge.

## Storage Element: Register (building block)

- Similar to a D Flip Flop except, N-bit input and output, write enable input. The write enable says "on the next clock edge do I write or not"

## Storage Element: Register File

- Register file consists of 32 registers: two 32 bit output busses, busA and busB.
- Separate set of 5 bits which give you the output for something... Two values coming out of that memory with two different addresses.
- Can also write to the register file. 5 bit port which says which register you want to update. Register will only be written if there's a rising clock edge and write enable is true.

## Step 3a: Instruction Fetch Unit

- PC (just a register), clock that goes to this register and there's some combinational logic which figures out what the next address should be.
- Instruction memory here

## Step 3b: Add & Subtract

- control unit looks at these and figures out how to decode it. Clock edge, start of one clock cycle.

## Clocking Methodology

- CPU we'll build is a simple unpipelined CPU. Every instruction takes one clock cycle. All phases of an instruction in one clock cycle. All signal propagates through the whole machine so you can updateeverything.
- If it's going to update, you can do it in one place.
- Only change at the clock edge. Signals propagate through.
- Critical path, longest path through logic, is what determines your length of clock period. If you try to go faster than this, you'll sometimes get an incorrect result. Architects spend a looot of time trying to shrink the critical path. How do you make the system run fast.
