# Lecture 1

## Anatomy of a Stack Frame

- When you call functions in C, the first thing that happens is the parameters get pushed onto the stack.
- Then you have this ASM `call` function that pushes your current address onto the stack so that when it returns you can come back to that same spot.
- Other memory will get assigned for other local variables and stuff.
- Stack grows down. But if you're filling a buffer you start at the bottom of this buffer and work your way up.
- The problem happens if you write too much and your content that you write is bigger than the buffer itself. C doesn't do bounds checks at runtime. There's nothing to prevent you from overwriting memory as you go up the stack.
- The really bad thing is someone malicious could come in and write a bunch of assembly and get that to be executed.
- This problem is called a buffer overflow.

- Comprehensive Experimental Analyses of Automotive Attack Surfaces, will interesting paper.

## Why not use GC'ed languages?

- Expensive: No matter what type of GC is used, there's always going to be memory overhead
- Disruptive: There's always gonna be GC pauses
- Non-deterministic. Whens the next GC pause going to be?
- No manual optimisation: Sometimes you wanna lay out memory in your own way.
- Discord moved from Go to RUst because you can see big latency spikes every 2 minutes and these correspond to "stop the world" GC pauses.
- Latency is really important in things like games, UIs, self-driving cars, payment processing.
- Even if you have GCs, you still have other memory issues like race conditions.

Based off CS107 and CS110, so maybe look at those if you start getting stuck...