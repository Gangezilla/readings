Questions: http://inst.eecs.berkeley.edu/~cs61c/sp15/disc/00/Disc0.pdf

Answers: http://inst.eecs.berkeley.edu/~cs61c/sp15/disc/00/Disc0Sol.pdf

# 1 Unsigned Integers

## 1.1

0b10010011: base 10: 147, hex: 93

0xD3AD: binary: 0b1101_0011_1010_1101. decimal: 54189

63: binary: 0b0011_1111, hex: 3F

0b0010_0100: decimal: 36, hex: 24

0xB33F: binary: 0b1011_0011_0011_1111. decimal: 45887

0: binary: 0b0000_0000, hex: 0

39: binary: 0b0010_0111. hex: 27

0x7EC4: 0b0111_1110_1100_0100. decimal: 32452

437: binary: 0b0000_0001-1011_0101. hex: 1B5

# 2 Signed Integers

## Two's Complement

To flip the sign of a two's complement number, you invert all the bits and add 1
1: Unsigned: [255, 0]. Signed: [-127, 128]
2: Unsigned: 0: 0b0000_0000. 1: 0b0000_0001. -1: N/A. Signed: 0b0000_0000. 1: 0b0000_0001. -1: 0b1111_1111
3: Represent 17 and -17: Unsigned: 17: 0b0001_0001. -17: N/A. Signed: 17: 0b0001_0001. -17: 0b1110_1111
4: The largest integer that gets set is arbitrary, based on deciding where you started counting.

# 3 Counting

1: 2
2: 42 bits
3: 0
