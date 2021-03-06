# The Abstraction: Address Spaces

Every address generated by a user program is a virtual address

## Early Systems

Early machines didn't provide much of an abstraction to users. Basically, the physical memory of the machine was basically split into the OS and the currently running program. The OS was a set of routines that sat in memory and there would be one running program that sat in physical memory and used the rest of memory.

## Multiprogramming and time sharing

Multiprogramming came about when people started to share machines, and it allows multiple processes to run at a given time with the OS switching between them. This increased the utilisation of the CPU and made each computer more efficient. This was v important when computers cost hundreds of thousands (or millions) of dollars.

Soon after, the notion of interactivity became important as many people might be using a machine and hoping for a timely response. Allowing multiple programs to reside concurrently in memory makes protection an important issue, as you don't want a process to be able to read or write some other process's memory.

## The address space

In order to do this, the OS creates an abstraction of physical memory called the **address space** which is the running program's view of memory in the system.

The address space contains all of the memory state of the running program. For example, the code of the program is in the address space. While the program is running, the stack it uses to keep track of where it is in the function call chain as well as hold its local variables is held in the address space. As is the heap, which is used for dynamically-allocated user-managed memory.

With the memory that we have, the program code lives at the top of the address space. Beneath this is the heap which grows positively (downwards), and then at the bottom of the address space we have the stack which grows negatively (upwards). We place the heap and stack like this because both want to grow, and this allows them to do so. 

When we describe the address space, we're describing an abstraction that the OS is providing to the running program. When the OS does this, we say the OS is **virtualising memory** because the running program thinks its loaded into memory at a particular address and has a potentially very large address space, the reality is quite different.

When a process tries to perform a load at address 0 (which we call a **virtual address**), somehow the OS (with some hardware support) has to make sure the load doesn't go to physical address 0 and instead goes to where the process is actually loaded into memory. This is the key to virtualisation of memory, which underlies every modern computer system.

## Goals

Thus, the OS must virtualise memory. The goals of an OS in doing so are as follows:

1) Transparency: The OS should implement virtual memory (VM) in a way that's invisible to the running program. Thus, the program shouldn't know it's memory is virtualized. Behind the scenes, the OS does all the work to multiplex memory and a bunch of other stuff
2) Efficiency: The OS should strive to make virtualization as efficient as possible.
3) Protection: The OS should make sure to protect processes from one another as well as the OS itself. When a process performs a load or a store, it should not be able to access or affect anything that is outside of its memory contents. Protection lets us deliver the property of isolation among processes.

Side note: Isolation is a key principle in building reliable systems. If two entities are properly isolated from one another, it implies one can fail without affecting the other. 

## Summary

We've spoken about virtual memory (VM), which is a system responsible for providing the illusion of a large, sparse, private address space to programs which hold all their instructions and data. The OS takes these virtual memory references and turns them into physical addresses. The OS does this for many processes at once, making sure to protect them from one another as well as the OS.

For example, if you print out a pointer in a C program, you'll get a big hex number which is a virtual address. Because of this, this is only a virtual address; only the OS truly knows where in physical memory this address lies. If we print out the address spaces for code, heap and stack. We see that the code is at the front, with the heap following closely behind, and then the stack is all the way at the back of this virtual address space.