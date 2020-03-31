# Representations of Combinational Logic Circuits

<http://inst.eecs.berkeley.edu/~cs61c/resources/boolean.pdf>

## Introduction

- We previously learnt that every register has the same internal structure.
- Combinational logic (CL) blocks are all different from each other where the internal circuit structure is tailored to the functional requirements of that particular circuit.

## Truth Tables

- Combinational logic circuit behaviour can be specified by looking at the relationship between the input and output values because for each input pattern of 1's and 0's, there exists a single output pattern. This is commonly shown in a truth table that looks like this:

a b c d y
0 0 0 0 F(0,0,0,0)
0 0 0 1 F(0,0,0,1)
0 0 1 0 F(0,0,1,0)
0 0 1 1 F(0,0,1,1)
0 1 0 0 F(0,1,0,0)
0 1 0 1 F(0,1,0,1)
0 1 1 0 F(0,1,1,0)

- For each row of the table, the output column shows the output value of the block for the input pattern.
- Many CL blocks have more than one output, or a single output that is more than one bit wide. They're often combined into a single table with multiple output columns, one for each single-bit output.
- A good example of this is a 2 bit wide unsigned adder circuit, with a 3 bit wide output. Part of it's truth table looks like this. As you can see, we just add the binary numbers together and then output them.

A B C
a1a0 b1b0 c2c1c0
00 00 000
00 01 001
00 10 010
00 11 011
01 00 001
01 01 010

- In principle, the function of any combination logic circuit can be completely specified with truth tables, but in practice some are too big. For example, a 32 bit unsigned adder with 33 bit output has 24^6 rows.

## Logic Gates

- What do we do if we need to determine the circuit details for a combinational logic block? In most cases we will use a collection of smaller combination logic circuits called logic gates. Logic gates are simple circuits (with only a handful of transistors each) that can be wired together to implement any CL function.
- There's diagrams in the above PDF, but you've got a few common gates such as: AND, OR, NOT, XOR, NAND, NOR.
- You'll generally only need a subset of these logic gates to implement a particular function.

## Boolean Algebra

- George Boole (19th centure mathematician) developed a mathematical system involving logic that became known as Boolean Algebra. His variables took on the values of TRUE and FALSE. Later on, Claude Shannon showed how to map Boolean algebra to digital circuits.
- The primitive functions of Boolean algebra are AND, OR, and NOT. They're powerful because we can represent a Boolean equation with AND, OR and NOT gates.
- The majority function is `y = a.b + a.c + a.c` (where . is AND and + is OR). You can then use this to sketch up a diagram of what this component should look like and then implement it.
- A bar over a variable indicates the variable is inverted and becomes a NOT.
- The value of Boolean algebra for circuit design comes from the fact that Boolean expressions can be manipulated mathematically. For instance, an expression can be simplified, which leads directly to a circuit simplification.

y = ab + a + c equation derived from original circuit
↓
ab + a + c algebraic simplification
= a(b + 1) + c
= a(1) + c
= a + c

### Laws of Boolean Algebra

- There's a number of laws that apply to Boolean expressions.

## Summary

- There's three representations of a component: truth table, boolean expression, gate diagram.
