# Processes

Here we discuss one of the most fundamental abstractions that the OS provides to users: the process. The definition of a process is pretty simple, it's essentailly just a running program. A program itself is a bunch of instructions waiting to spring into action, and the OS takes these bytes and gets them running transforming the program into something useful. This allows us to run multiple programs at once. This makes a system easy to use because we don't need to be concerned with whether a CPU is available, you just run a program.

**The crux of the problem is**: How do we provide the illusion of many CPUs?
Although there are only a few physical CPUs available, how can the OS provide the illusion of a nearly-endless supply of said CPUs?

The OS creates this illusion by virtualizing the CPU. By running one process then stopping it and running another and so forth, the OS can promote the illusion that many virtual CPUs exist when in fact there's only one physical CPU. This is a basic technique known as **time sharing** of the CPU, which allows many concurrent processes to be run.

To implement virtualization the OS needs low-level machinery and high-level intelligence. We call the low-level machinery, mechanisms, which are low-level methods or protocols that implement a needed piece of functionality. We can use techniques like **time sharing**, which allows an OS to share a resource and **space sharing**, where a resource is divided among those who wish to use it. For example, disk space is naturally a space shared resource. On top of this you have some of the high-level intelligence in the form of **policies**. A policy is an algo for making some kind of decision in the OS, like, a scheduling policy will decide which program to run given a number of programs.

## The Abstraction: A Process

The abstraction provided by the OS of a running program is something we'll call a **process** and at any point in time we can summarize a process by taking an inventory of the different pieces of the system it accesses ora ffects during the course of its execution. To understand what constitutes a process, we have to understand its **machine state**, which is what a program can read or update when it's running.

At any given time, what parts of the machine are important to the execution of this program? Part of this is _memory_ as instructions live in memory, as does the data that the running program reads and writes. Thus the memory that the program can address (called it's address space) is part of the process. Also part of the process's machine states are registers as many instructions read or update registers. There's also special registers like the **program counter (PC)** and **instruction pointer (IP)** that tell us which instruction will execute next.

When implementing this, a common pattern is to separate high-level policies from low-level mechanisms. Think of the mechanism as providing the answer to a _how_ question, such as how does an OS perform a context switch? The policy answers a _which_ question, like which process should the OS run right now?

## Process API

These are some things that must be included in any OS interface:

- Create: An OS must include some method to create new processes. When you type a command into the shell or double-click an app icon, the OS is invoked to create a new process
- Destroy: Many processes will run and exit by themselves, but when they don't, you need a way to kill them.
- Wait: Sometimes its useful to wait for a process to stop running; thus some kind of waiting interface is provided.
- Misc control: Apart from killing or waiting, sometimes you'd want to suspend a process or resume it, for example.
- Status: Get some status info about a process like how long its run for or what state it's in.

## Process Creation

How are programs transformed into processes? Specifically, how does the OS get a program up and running?

The first thing that the OS does is load a program's code and static data into memory into the address space of the process. Programs initially reside on disk in an executable format. Thus, the process of loading a program and static data into memory requires the OS to read those bytes from disk and place them in memory somewhere. In early OS's the loading process is done eagerly, meaning all at once before running the program. Modern OSes perform this lazily, meaning they load code or data as they're needed. This ties into the concepts of paging and swapping which we look at later. Once the code and static data are loaded into memory, the OS must alloce some memory for the program's **run-time stack**. C programs use the stack for local variables, function params and return addresses. The OS allocates this memory and gives it to the process. The OS will also likely initialize the stack with arguments; specifically, it will fill in the params to the `main()` function. The OS may also allocate some memory for the heap, where (at least C programs) dynamically allocated data (like `malloc()` and `calloc()`) get their memory from. By loading the code and static data into memory the OS has now set the stage for program execution. It then starts the program by running the `main()` function.

## Process States

A process can be in different states, such as:

- Running: Where a process is executing instructions on a processor.
- Ready: A process is ready to run but the OS has chosen not to run it for some reason.
- Blocked: In the blocked state, a process has performed some operation that makes it not ready to run until another event takes place, like I/O request to disk or something.

Being moved from ready to running means the process has been scheduled. Being moved from running to ready means the process has been descheduled. Once a process has become blocked, the OS will keep it as such until some event occurs. At that point, the process moves to the ready state again.

## Data Structures

The OS is a program, and like any program, it has some key data structures that track various pieces of information. To track the state of each process, for example, the OS likely will keep some kind of process list for all processes. The OS must also track blocked processes.

## Summary

- The process is the major OS abstraction of a running program. At any point in time, the process can be described by its state: the contents of memory in its address space, the contents of CPU registers and information about I/O.
- The process API consists of calls programs can make related to processes. Typically this includes creation, destruction and other useful calls.
- Processes exist in one of many different process states, including running, ready to run and blocked.
- A process list contains information about all processes in the system. Each entry is found in what is sometimes called a process control block (PCB) which is really just a structure that contains info about a specific process.
