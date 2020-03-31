# B.2 - B.3

## B.2 - Gates, Truth Tables and Logic Equations

- The electronics inside a modern computer are digital. Digital electronics operate with only two voltage levels of interest. When the level is high, we say it's true or _asserted_, and when it's low, we say it's false or _deasserted_.
- Logic blocks are categorized as _combinational_ if they don't contain memory, and their output is only dependent on current input.
- In blocks with memory, or, _sequential logic_ the output depends on input and what's in memory, or _state_.

### Truth Tables

- Because a combinational logic block contains no memory, it can be completely specified by defining the values of the outputs for each possible set of input values. Truth tables can completely describe any combinational logic function, but can grow and be hard to understand quite fast.

### Boolean Algebra

- Another approach is to express the logic function with logic equations...

## B.3 - Combinational Logic

### Decoders

- One logic block that we will use in building larger components is a _decoder_. The most common type of decoder has an n-bit input and 2^n outputs, where only one output is asserted for each input combination. The decoder translates the n-bit input into a signal that corresponds to the binary value of the n-bit input.

### Multiplexors

- A multiplexor might more properly be called a selector, since its output is one of the inputs that is selected by a control.
- Consider the two-input multiplexor, which actually has three inputs. Two data values, and a selector (or control) value. The selector value determines which of the inputs becomes the output.

### Two-Level Logic and PLAs

- So, any logic function can be implemented with only AND, OR, and NOT functions. Any logic function can be written in a canonical form as an equation. It's usually structured in what's called a _sum of products_ form.
- We can use the relationship between a truth table and a two level representation to generate a gate-level implementation of any set of logic functions.
- The sum of products representation corresponds to a common structured logic implementation called a _programmable logic array (PLA)_. A PLA has a set of inputs and input complements, and two stages of logic. The first stage is an array of AND gates that form _product terms_, where each product term can consist of any of the inputs or their complements. The second stage is an array of OR gates, each of which forms a logical sum of any number of the product terms.

## ROMs

- Another form of structured logic that can be used to implement a set of logic functions is a _read-only memory (ROM)_. A ROM is called memory because it has a set of locations that can be read, and these are fixed at the time of manufacture.
- There's also _programmable ROMs (PROMs)_, which can be programmed electronically.
- A rom has a set of input address lines and outputs, the number of addressable entries in ROM determines the number of address lines.
- A ROM can encode a collection of logic functions direct from the truth table.

## Don't Cares

- Sometimes when implementing combinational logic, we don't care what the output is, because some other output is true or a subset of input determines the value of output. These situations are called _don't cares_
- There's two types of don't cares, output and input don't cares. On a truth table, a don't care is represented as an X.
- This is useful cos it allows us to do logic minimization, which is critical to efficient implementation.

## Arrays of Logic Elements

- Many of the combinational operations to be performed on data have to be done to an entire word (32 bits) of data. Thus we often want to build an array of logic elements which is represented by showing that a given operation will happen to an entire collection of inputs. Inside a machine, much of the time we want to select between a pair of _buses_.
- A _bus_ is a collection of data lines that are treated as a single logical signal.
- For example in MIPS, the result of an instruction thats written into a register can come from one of two sources. A multiplexor is used to choose which of the two buses will be written into the result register