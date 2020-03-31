# MIPS II / Instruction Formats

## 1. Translate the following C code into MIPS

```c
// Strcpy:
// $s1 -> char s1[] = “Hello!”;
// $s2 -> char *s2 =
// malloc(sizeof(char)*7);
int i=0;
do {
 s2[i] = s1[i];
 i++;
} while(s1[i] != '\0');
s2[i] = '\0';
```

```asm
# $t0 = i, $t1 = pointer to s1, $t2 = pointer to $s2
# $t3 = temp value to hold char
addi $t0, $0, 0 # putting 0 in $t0 (int i = 0;)
Loop: addu $t1, $s1, $t0 # s1[i]
      addu $t2, $s2, $t0 # s2[i]
      lb $t3, 0($t1) # grab the byte from string one at i and put it into $t3
      sb $t3, 0($t2) # grab our byte from $t3 and put it into $s2[i]
      # the 0 in the above means offset of 0
      addiu $t0, $t0, 1 # increment $t0 by 1
      addiu $t1, $t1, 1 # increment $t1 by 1
      lb $t4, 0($t1) # put the current char of s1 into $t4 (to check if null)
      bne $t4, $0, Loop # check if string 1 has ended, if not, go back to start of loop. if it has, drop through
Done: sb $t4, 1($t2) # cos we're done, this is the last character of s1, so we store it at an offset of 1 in s2.
# offset of 1 because if we didn't, we'd overwrite the last char from the loop.
```

```c
// Nth_Fibonacci(n):
// $s0 -> n, $s1 -> fib
// $t0 -> i, $t1 -> j
// Assume fib, i, j are these values
int fib = 1, i = 1, j = 1;
if (n==0) return 0;
else if (n==1) return 1;
n -= 2;
while (n != 0) {
 fib = i + j;
 j = i;
 i = fib;
 n--;
}
return fib;
```

```asm
 # $s0 = n, $s1 = fib
 # $t0 = i, $t1 = j

 beq $s0, $0, Ret0 # if n == 0, go to Ret0
 addiu $t2, $0, 1 # put 1 into $t2 for comparison
 beq $s0, $t2, Ret1 # if n == 1, go to Ret1
 addiu $s0, $s0, -2 # n -= 2;
Loop: beq $s0, $0, RetF # if n == 0, exit function
  addu $s1, $t0, $t1 # fib = i + j
  addiu $t0, $t1, 0 # i = j
  addiu $t1, $s1, 0 # j = fib;
  addiu $s0, $s0, -1 # n--;
  j Loop
Ret0: addiu $v0, $0, 0 # put 0 in return value exit
  j Done
Ret1: addiu $v0, $0, 1 # if n == 1, return 1
  j Done
RetF: addu $v0, $0, $s1 # if n == 0, return fib
Done: ...
```

```c
// Collatz conjecture
// $s0 -> n
unsigned n;
L1: if (n % 2) goto L2;
goto L3;
L2: if (n == 1) goto L4;
n = 3 * n + 1;
goto L1;
L3: n = n >> 1;
goto L1;
L4: return n;
```

```asm
# $s0 -> n
L1: addiu $t0, $0, 2 # add 2 to temp value
 div $s0, $t0 # puts (n%2) in $hi (high register)
 mfhi $t0 # sets $t0 = (n%2) mfhi is move from hi
 bne $t0, $0, L2 # go to L2 if (n % 2)
 j L3 # else jump to L3
L2: addiu $t0, $0, 1 # add 1 to temp register
 beq $s0, $t0, L4 # if n == 1, go to L4
 addiu $t0, $0, 3 # add 3 to temp register (which we know is 1)
 mul $s0, $s0, $t0 # multiply n by temp register
 addiu $s0, $s0, 1 # add 1 to n
 j L1 # go to L1
L3: srl $s0, $s0, 1 # shift right logical by 1
 j L1 # go to L1
L4: ...
```
