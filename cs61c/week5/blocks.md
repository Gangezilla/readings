# Combinational Logic Blocks

<http://inst.eecs.berkeley.edu/~cs61c/resources/blocks.pdf>

## Data Multiplexors

- A data multiplexor (mux) is a circut that selects its output value from a set of input values.
- A regular mux has two n-bit inputs, A and B, and an n-bit output, C. Additionally it has a signal labeled s for select, this is used to control which of the two input values to output.
- To come up with the logic equation and the associated gate-level circuit diagram we can apply the technique that we studied last lecture.
- A 4bit mux is made of 3 other mux's, with two select bits.

## ALU

- A common way to implement an ALU is to provide a CL block for each of the possible ALU functions. Therefore, we get a subtractor/adder, an AND block, and an OR block and combine it all together. The adder block has a special overflow output where a 1 is outputted if it overflows.
- The high bit, s1, is used to choose between add/subtract, and the output of the mux that did the AND or OR. The choice of AND/OR or add/subtract is controlled by s0.

## Adder/Subtractor Design

- One obvious method would be to start with a truth table and simplify, but this only works for narrow adders and not wide ones because the truth table gets too large.
- Long hand addition is a good model, when we add by hand we add the least significant bits, then generate a result bit and maybe a carry bit.
- We can break the adder up into multiple equations which correspond to certain components.
- Subtraction is similar to addition. We can use two's complement to augment our adder. There's more details in the PDF if you need them.
