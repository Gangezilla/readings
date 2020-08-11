# Mechanism: Limited Direct Execution

There are a few challenges with time sharing a CPU:

1) Performance; How can we implement virtualization without adding excessive overhead to the system? 
2) Control; How can we run processes efficiently while retaining control over the CPU?

Control is particularly important to the OS, as it is in charge of resources. Without control, a process could simply run forever and take over the machine, or access info it shouldn't be allowed to.

Obtaining high performance while maintaining control is one of the central challenges in building an operating system.

The OS must virtualize the CPU in an efficient manner while retaining control over the system. To do so, both hardware and OS support will be required.

## Basic Technique: Limited Direct Execution

To make a program run fast, OS devs came up with a technique we call **limited direct execution**. The 'direct execution' part means run the program directly on the CPU. Thus, when the OS wishes to start a program running, it:

OS                                                      Program

1) creates a process entry for it in a process list
2) allocates some memory for it
3) loads the program code into memory
4) Set up stack with argc/argv
5) Clear registers
6) Execute call main()
                                                        7) Run main()
                                                        8) Execute return from main
9) Free memory of process
10) Remove from process list

This leads to a few issues to think about:

1) If we just run a program, how can the OS make sure it doesn't do anything that we don't want it to do.
2) When we run a process, how does the OS stop it from running and switch to another process, thus implementing the **time sharing** we require to virtualize the CPU.

## Problem #1: Restricted Operations

What if the process wishes to perform some kind of restricted operation, such as issuing an I/O request to a disk, or gaining access to more system resources like CPU or memory? The approach we take to this is to introduce a new processor mode known as **user mode**, meaning code that runs in this mode is restricted in what it can and can't do. If a program tries to do something restricted, the OS will kill the process. The alternative to this is **kernel mode** which the OS runs in. In this mode, code that runs can do what it likes including privileged operations.

When a user's program wants to do something restricted, we provide the ability for user programs to perform a **system call** which allow the kernel to carefully expose certain key pieces of functionality to user programs like accessing the file system. It's basically a system API, where the system exposes a number (a few hundred) calls which do a certain thing. To execute a system call, a program must execute a special **trap** instruction which jumps into the kernel and raises the privilege level to kernel mode; allowing the system to perform the privileged operation. When finished, the OS calls a special **return-from-trap** instruction which returns to the calling user program and reduces the privilege level back to user mode.

The hardware must make sure it saves the caller's registers in order to be able to return correctly. On x86, the processor will push the program counter, flags and a few registers onto a per-process **kernel stack** and these will get popped off. The trap knows which code to run based off of a **trap table**. This allows the OS to tell the hardware what code should run when certain events take place.

To specify the exact system call, a **system-call number** is assigned to each system call. The user code is responsible for placing the desired system-call number in a register or at a specified location on the stack. The OS will examine this number and execute the code if it's valid.

## Problem #2: Switching Between Processes

The problem here is that when a process is running on the CPU, it means the OS is *not* running. If the OS isn't running, how can it do anything?

**How can the OS regain control of the CPU so it can switch between processes?**

### A cooperative approach

Some systems like early Macintosh OSs use a **cooperative** approach. This means the OS trusts the processes of the system to behave reasonably. A friendly process transfers control to the OS frequently through the use of system calls. Systems like this often include an explicit **yield** system call which transfers control to the OS. The OS also transfers control when it tries to do something illegal by generating a trap to the OS which transfers control.

However, if no system calls are made, or like, an infinite loop occurs. You have to reboot your machine. This is less than ideal.

### A non-cooperative approach

Another approach is to use a **timer interrupt**. A timer device can be programmed to raise an interrupt every x milliseconds which means the process is halted, and a pre-configured **interrupt handler** in the OS runs. At this point, the OS has regained control of the CPU and can do what it pleases.

Once the timer has begun, the OS can feel safe in that control will eventually be returned to it.

### Saving and restoring context

Now that the OS has control, it has to decide to continue running the currently-running process or switch to a different one. This decision is made by the **scheduler**. If a switch is made, the OS executes a low-level piece of code we refer to as a context switch. A context switch is conceptually simple, all the OS has to do is save a few register values for the currently executing process and restore a few for the soon to be executing process. This means the OS ensures that when the return-from-trap instruction is executed, instead of returning to the process that was running, the system resumes execution of another process.

## Summary

The basic idea of limited direct execution is simple: Run the program you want to on the CPU, but first make sure to set up the hardware so as to limit what the process can do without OS assistance.

This general approach is taken IRL, for example, with baby proofing a room. Similarly, the OS baby proofs the CPU by first (during boot time) setting up the trap handlers and starting an interrupt timer, and then by only running processes in a restricted mode. By doing so, the OS can feel assured that processes can run efficiently only requiring OS intervention to perform privileged operations or when they need to be switched out.

- The CPU should support a restricted user mode, and a privileged (non-restricted) kernel mode.
- Typical user apps run in user mode, and use a system call to trap into the kernel to request OS services.
- The trap instruction saves register state carefully, changing the hardware status to kernel mode and jumps into the OS to a pre-specified definition: the trap table.
- When the OS finishes a system call, it returns to the user program via a special return-from-trap instruction which reduces privilege and returns control to the instruction after the trap that jumped into the OS.
- Trap tables must be set up at boot time.
- Once a program is running, the OS must use hardware mechanisms to ensure the program doesn't run forever, namely the timer interrupt.
- Sometimes the OS during a timer interrupt or system call might switch to a different program, which is called a context switch.