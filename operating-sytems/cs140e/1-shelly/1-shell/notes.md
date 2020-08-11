# Notes

## Questions

### In assignment 0, you enabled GPIO pin 16 as an output and then repeatedly set and cleared it by writing to registers GPFSEL1, GPSET0, and GPCLR0. Which three registers would you write to to do the same for GPIO pin 27? Which physical pin on the Raspberry Pi maps to GPIO pin 27?

We set pins by shifting a 1 the required number of places. So for pin 16 we write to these registers:

```
GPIO_FSEL: 0b1 << 18
GPIO_SET0: 0b1 << 16;
GPIO_CLR0: 0b1 << 16;
```

For pin 27 we'd do something similar:

```bash
GPIO_FSEL2: 0b1 << 27
GPIO_SET0: 0b1 << 27;
GPIO_CLR0: 0b1 << 27;
```

FSEL contains 10 pins per register (three bits per pin), so the 27th register will be stored in GPIO_FSEL2.

SET/CLEAR store 32 pins per register (one bit per pin), so GPIO pin 27 would be in GPIO_SET0 and GPIO_CLR0.