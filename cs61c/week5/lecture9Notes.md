# Intro to Synchronous Digital Systems (SDS), Logic - 2015-02-17

## Hardware Design

- Next several weeks we'll go from how a modern processor is built starting with basic elements.
- It's important to study hardware, because knowing how the hardware works is the best way to extract peak efficiency out of hardware. Helps you figure out what's fast and what's slow to do. Getting into hardware design is good, also a great way to make some great money too.
- It's hard to know what's coming up in 30 years, so good to understand now since Moore's Law is ending.
- Some places do custom hardware, cos there's only so much you can do with standard processors.

## Synchronous Digital Systems

- Synchronous System thats guided by a clock. There's a global clock tick which orchestrates behaviour. The processor speed is the speed of the clock in the computer.
- Digital Systems have discrete steps, represents all values. Electrical signals are treated as 1's and 0's or high/low voltage.

## Switches: Basic Element of Physical Implementations

- Diagrams, when switch is open no current can flow and the bulb is off. When the switch is closed, current can flow and the lightbulb is on.
- You can then compose those switches into more complex ones. I can implement logical AND and logical OR functions with these switches too.
- Early computer designers built ad hoc circuits from switches. They began to notice commonh patterns in AND's and OR's. A Master's thesis made link between work and 19th centure mathemtician George Boole.

## Transistors

- A computer needs a switch to be controlled by other switches, once you've got that you can build a computer. These switches these days are CMOS transistors.
- We use voltage to represent 0 and 1.
- Modern digital systems designed in CMOS. MOS: Metal Oxide on Semiconductor. C for complementary, use pairs of normally-open and normally-closed switches.
- CMOS transistors act as voltage-controlled switches. Sandwich of metal oxide.
- CMOS Transistors: 3 terminals: Source, gate and drain

  - If voltage on gate terminal is higher/lower than source terminal, then conducting path established between drain and source terminals
  - This is an n-type transistor: When gate voltage is 1, source and drain are connected. Disconnected at 0. A p-type transistor is opposite.

## Moore's Law

- Doubling number of transistors per chip every 18 months. Billions of logic transistors on a single chip.
- It's amazing that all transistors can be arbitrarily linked together in lots of sheets of metal. Transistors are really really tiny. Everything that exists on a chip is just transistors. P and N transistors make everything on a computer chip from processor to memory.

## CMOS Circuit Rules

- N-type passes weak 1's but strong 0's.
- P-Type passes weak 0's but strong 1's.
- Using them in pairs gives you strong values.

## CMOS Networks

- You can create an inverter or not gate using 2 transistors.
- You can create any computer you can imagine using just NAND gates.

## Combinational Logic Symbols

- Common combinational logic systems have standard symbols called logic gates.
- Buffer, NOT right facing triangle.
- AND, NAND: little hemisphere with a flat left bum, with a dot on the side if its NAND
- OR, NOR: hemisphere with rounded bum, dot on side if its NOR.

## Truth Tables

- Truth Table is an exhaustive listing of every combintation of input values, what should be the output value.
- A logic gate can only possibly take in a bit, so you should think about it in this context too.

## Boolean Algebra

- Use + for OR (logical sum)
- Use product (dot) for AND (a dot b) (logical product)

## Laws of Boolean Algegra

- There's a bunch of these laws...
- If you take a number and AND it with itself it's always 0. If you OR them, it'll be a 1 (complementarity)

- In hardware everything happens in parallel, in software you get to step through stuff one by one.

## Types of Circuits

- Synchronous Digital System
  - Combinational Logic circuits, where output is a function of inputs only and not the history of its execution.
  - Sequential Logic is stuff that remembers state such as memory and registers.
- Using a register lets us hold a value and we can then do something with this
