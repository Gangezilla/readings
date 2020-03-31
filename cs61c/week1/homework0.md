http://inst.eecs.berkeley.edu/~cs61c/sp15/hw/00/hw0.html

# Problem 1:

Unsigned
Decimal Binary Hexadecimal
10 0b0000_1010 0x0A
240 0b1111_0000 0xF0
15 0b0000_1111 0x0F
161 0b1010_0001 0xA1
250 0b1111_1010 0xFA

Knowing that each number in a hex value is 4 bits, once you have the binary rep you can sum it up from there.

# Problem 2:

You would like to represent the temperature in degrees Celsius: TWO'S COMPLEMENT because a temperature can be a negative number

You would like to maximize the range (distance between most negative represented number, and most positive represented number): UNSIGNED, because a range between two numbers will be positive.

You would like to represent the number of boxes a factory has shipped: UNSIGNED, because its either gonna be 0 or greater than 0.
