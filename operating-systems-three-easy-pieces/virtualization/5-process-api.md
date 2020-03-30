# Interlude: Process API

Unix presents one of the most intriguing ways to create a new process with a pair of system calls: `fork()` and `exec()`. A third routine `wait()` can be used by a process wishing to wait for a process it has created to complete.

**The crux of the problem is:** What interfaces should the OS present for process creation and control? How should these interfaces be designed to enable powerful functionality, ease of use and high performance?

## The `fork()` system call

The `fork()` system call is used to create a new process, but it's a strange one. More specifically, you have a running program whose code looks like the included fork-example.c. Fork has a weird API, so let's run through it. When this program first starts running, the process prints out a hellow world message with a PID. After that, the process calls `fork()` which the OS provides as a way to create a new process. The odd thing is that the process that gets created is an (almost) exact copy of the calling process. To the OS, it now looks like there are two copies of the program running and both are about to return from `fork()`. The newly-created process doesn't start running at `main()` rather it just comes into life as if it has called `fork()` itself. The child isn't an exact copy. Specifically, it has its own PC and so forth.

The CPU scheduler determines which process runs at a given moment in time; although due to the scheduler's complexity we can't determine which process will run first. This non-determinism leads to some problems, particularly in multi-threaded programs.

## The `wait()` system call

Sometimes its quite useful to wait for a child process to finish what its been doing, and we do that by using the `wait()` system call.

## The `exec()` system call

A final and important piece of the process creation API is the `exec()` system call. This system call is useful when you want to run a program that's different from the calling program. `exec()` is really useful in that it lets us call a different program altogether. `exec()` takes the name of the program and a list of arguments in a way similar to invoking a c program.

## Why? Motivating the API

Separating `fork()` and `exec()` is essential in building a Unix shell because it lets the shell run code after the call to `fork()` but before the call to `exec()`. This means the code can alter the environment of the about-to-be-run program. The shell is just a program that shows you a prompt. The shell then figures out where in the file system the executable resides, calls `fork()` to create a new child process to run the command. It then calls some variant of `exec()` to run the command and waits for the command to complete by calling `wait()`.

## Process Control and Users

There's lots of other ways to interact with processes in Unix systems. `kill()` for example lets you send signals to a process. Certain key commands are configured to deliver a specific signal to the currently running process, such as ctrl-c sending a SIGINT (interrupt) message.
