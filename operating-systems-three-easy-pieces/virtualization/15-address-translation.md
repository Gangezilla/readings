# Mechanism: Address Translation

When we looked at virtualizing the CPU, we focused on a limited direct execution (LDE). Basically, LDE says we let the program run directly on the hardware but we design it so that sometimes the OS can get involved and make sure that the "right" thing happens. The OS tries to get out of the way of te running program to deliver an efficient virtualisation, but by **interposing** at certain points in time the OS ensures that it maintains control over the hardware.

> Efficiency and control together are two of the main goals of any modern OS.

In virtualizing memory we have the same goals.

- Build an efficient virtualization of memory
- Provide flexibility needed by applications
- Maintain control over which memory locations an app can access

The generic technique we use is called **hardware-based address translation** or just address translation. This means when an application provides a virtual address for memory access, the hardware translates this to a physical address where the memory is located on hardware. The OS gets involved at some points to set up the hardware. This means that it **manages memory**; keeping track of which locations are free, which are in use and intervening to maintain control over how memory is used.

This leads to the illusion of heaps of stuff running at once, while under the hood the CPU switches between heaps of programs and everything shares one big bank of memory.

## Assumptions

- The user's address space (is the range of valid addresses in memory that are available for a program) is placed contiguously in memory.
- The size of the address space is not too big, meaning less than the size of physical memory.
- Each address space is exactly the same size.

## Example
