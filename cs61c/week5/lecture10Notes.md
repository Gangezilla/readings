# Functional Units, FSMs - 2015-02-19

## Types of Circuits

- When you're building digital systems, the systems are divided into two key types:
  - Combinational Logic (CL): Output is a function of the inputs only, not the history of it's execution. Circuits to add A, B (ALUs)
  - Sequential Logic (SL): Circuits that remember or store information, memories and registers.
- Systems have both of these kinds of circuits

## Uses for State ELements

- Place to store values for later re-use: Registers and memory. Also use it to separate waves of logic. Because hardware works in parallel all the time.

## Accumulator Example

- The accumulator reads a series of values and sums them up. Very simple in C.
- A combinational logic just flows data through to the output, but it's hard without sequential logic.
- So we add a register, which is a storage element that's used to store the value of x. The register has an input and an output. Square wave clock sets when things change. On the high value of the clock signal, we add one more value.
- Registers separate combinational logic. Registers hold values stable for the next clock cycle, register sends it out on the output bus. Lock-step style system.

## Register Internals

- n instances ofa "Flip-Flop", named as such because the output flips and flops between 0 and 1.
- D is "data input" and Q is "data output". Also called "D type Flip-Flop"

## Flip-Flop Operation

- Edge triggered. On the rising edge of the clock, the input d is sampled and transferred to the output. At all other times, the input d is ignored.
- The way a flip-flop works is it needs a unit of time where the input is not changing.
- You want to make setup and hold time as small as possible. They work to reduce this but there's fundamental limits to how small you can make this. Make it so that the time between clock edges settles out. That's the notion of a critical path, have to make sure that
- Clock to queue delay, from when the clock edge happens, when does the output show up on the flip-flop. It's the worst case scenario.

Camera Analogy:

- Want to take a portrait. Setup time - don't move since about to take picture. Hold time - need to hold still after shutter opens until camera shutter closes. Time click to data - time from open shutter until you can see image on output.

## Accumulator

- Reset input to register is used to force it all to zeros
- Analyze circuit timing starting at the output of the register.
- When the data appears it goes around and then propagates through.
- In reality, things aren't quite as perfect. In good circuits, instability never happens around rising edge of clock.

## Maximum Clock Frequency

- Max frequency is just 1/Period

## Critical Path

- This is the one path that makes everything else wait cos it's slow. Good designers will look for a critical path and seek to minimise it.
- Pipelining to improve performance
- Insertion of register allows higher clock frequency. More outputs per second (higher bandwidth)

## Recap

- Clock (CLK) - steady square wave that synchs system
- Setup time - when the input must be stable before the rising edge of the CLK
- Hold time - when the input must be stable after the rising edge of the CLK.
- Flip-flop - one bit of state that samples every rising edge.
- CLK-to-Q - Delay, how long it takes the output to change, measured from the rising edge of the CLK.
- Flip-flop - one bit of state that samples every rising edge of the CLK
- Register - several bits of state that samples on rising edge of CLK or on LOAD.

## Finite State Machines Intro

- FSM is something with a finite number of states and moves between them with a transition function. Depending on the input, we move between and present some output.
- A register is used to hold the state that you're in. For every clock cycle, it advances to the next state. Combinational logic circuit is used to implement a function maps from present state and input to next state and output.
- Can generate a truth table for an FSM.
- You can translate between boolean expressions, to truth tables to gate diagrams. They're all representations of largely the same thing.

## Building Standard Functional Units

- Multiplexer, ALU, adder/subtractor
- Goign to focus on how to put together some building blocks

## Multiplexer

- Mux
- Multiplexer takes in two inputs, and a select signal. And you use the select signal to pick which of these values you want to send to the output. Looks like a trapezoid usually.
- N instances of 1-bit-wide mux. You now have to only worry about building
- Cos there's 3 inputs, we need 2^3 (8) rows in the truth table.
- Truth table is now a logic function which we can take and simplify as an algebraic expression.

- We can have a multiplexer with 4 inputs, which means we need a 2 bit select signal. This would have 64 rows in the truth table cos it has 2^6 inputs.
- You wire up 3 2 bit mux's to build a 4bit mux.
- Very very common component, most common thing you have apart from flip-flops and registers. Registers and mux's are 80-90% of all computers.

## ALU

- Arithmetic and Logic Unit (ALU) is the thing that does all the computation.
- We'll do a simple one that does +, -, ^, |
- Usually takes in two inputs and it has an input bit on the side which says what function we do.
- When you put numbers in, it does all the work for all of the instructions, and then chooses which one to output to you. Doesnt matter that you aren't using one. Everytime you use this block you figure out everything. The add and subtract are combined into one block and that gets chosen.
- Solid state, not really wearing out. Fine to have them all moving up and down. It doesn't hurt to have them all going, it's easier to have them all do their thing instead of figuring out how to stop some of them.
- Software and hardware are super different. These are all switches, think of it like lightbulbs. If I want to save a value, I take a picture of it and put it in a register.
