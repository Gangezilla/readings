# Introduction to Synchronous Digital Systems

<http://inst.eecs.berkeley.edu/~cs61c/resources/sds.pdf>

## Instruction Set Architecture

- One of the big ideas from this semester was that high level languages (C, C++) are converted to a list of assembly language instructions, which get converted to a set of machine instructions.
- The set of opcodes that a processor can carry out, along with a description of the processor "state" (or, registers) is called the Instruction Set Architecture (ISA). This is an abstraction of the hardware for the benefit of the software. It's kinda like a 2-way contract between the hardware and the software.
- The hardware promises that it will faithfully implement the ISA and the software promises to only try to do things supported by the ISA.
- This means the software can do whatever it wants within these constraints, and it knows it'll work. It also means the software doesn't need to care about how the hardware implements the ISA.
- The ISA is an abstraction and doesn't specify in detail how the instruction execution should be implemented. This means there are many different ways to design a processor.

## Physical Hardware

- In the world of chip design, area == cost. Bigger chips are much more expensive to make than smaller chips. Designers work hard to make each function as physically small as possible without hurting performance.
- All of the components are made up of the same thing: wires and transistors. These are called integrated circuits because they put multiple transistors and wire together to make a part.
- Early chips had a single transistor or two without the necessary wires.
- Small collections of transistors are joined to make simple functional blocks which are joined to make bigger blocks etc.
- Surrounding the inner part of the chip is a set of connections to the outside world, usually in the form of wires. In most computers this PCB would be the motherboard. Many pins are used to connect to the power supply, which drives the operations of the processor. The energy is used to move electric charge in circuits, and the process is dissipated as heat.

## Signals and Waveforms

- Another special connection to the chip is the clock input signal. The clock signal is generated on the motherboard and sent to the chip where it is distributed throughout the processor on interal wires.
- The clock signal is the heartbeat of the system. It controls the timing of the flow of the electric charge, and therefore it controls the flow of information.
- It basically looks like a very regular repeating square wave. The clock signal is a very important signal and is present in all synchronous digital systems.
- Most of the time, the signals are either high or low. When they're high or low, they're sometimes not at the extremes. Changes in the signals correspond to changes in the clock signal.
- By convention, low voltage is used to represent a binary 0 and high voltage represents a binary 1. Transistors are robust against small errors, if a signal is high enough or low enough its treated as a 1 or 0 respectively. In synchronous systems, all changes follow clock edges.
- Signal wires are often grouped together to transmit words of data. The drawing shows 4 wires used to transmit a 4-bit word. The waveform shows how the signals on the wires change over time. If you stack the wires on top of each other in the diagram you can understand a bit better when they're high and low and therefore grok what word is being transmitted. It's really cool actually.

## Circuit Delay

- An important property of digital circuits is that they cannot produce a result instantaneously. If we examine the input and output waveforms, we'd notice a small delay from when the inputs change to when the output has the new result.
- A measure of the delay from input to output is called the _propagation delay_, and is called the adder propagation delay.
- The propagation delay is always less than the clock period.

## Types of Circuits

- The adder circuit is an example of a type of circuit we call _combinational logic_. These circuits take their inputs and combine them to produce a new output after some delay.
- THe output is a function of nothing other than the inputs, like a mathematical function.
- Combinational logic circuits are used throughout processor implementations, providing all the necessary functions needed to execute instructions.

- The other type of circuit that's important are circuits that remember their inputs, such as a memory circuit that implements the registers in MIPS.
