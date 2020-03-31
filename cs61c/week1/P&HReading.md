## Section 2.4 Signed and Unsigned Numbers

- Binary digits are like the "atom" of computing.
- We number the bits 0, 1, 2, 3 from right to left
- Least significant bit is the bit on the far right, or bit 0. Most significant is on the far left.
- If the number you're representing can't be saved by the hardware bits, overflow occurs.

- Because computer programs calculate both positive and negatitve numbers, we need a representation that distinguishes the positive and negative.
- The convention for representing signed binary numbers is called _two's complement_ representation.
- Two's complement numbers has the advantage that all negative numbers have a 1 in the most significant bit, which is often called a _sign bit_.
- Memory addresses naturally start at 0 and continue to the largest address, negative addresses don't make much sense.

- When working with two's complement numbers you have some shortcuts.
- Invert every bit and then add one to the result
