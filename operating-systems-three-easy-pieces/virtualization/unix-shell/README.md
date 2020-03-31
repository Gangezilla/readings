# Unix Shell

This is one of the homework projects for getting a better understanding of how processes work in an OS.

## Program Specs

### Basic shell: wish

They say to call the shell wish for Wisconsin Shell, but I'm going to call mine schell for Scott Shell (clever, hey?).

1) basically an interactive loop that prints a `schell> ` prompt
2) Parse input
3) Execute the command specified on that line of input and wait for the command to finish
4) Do this until the user types exit

There's also going to be a batch mode that will let you type `./schell batch.txt` and it'll read and run the instructions within that file.

Structure your shell so that it:

1) Creates a new process for each command
2) It should be able to parse a command run the program corresponding to the command. If a user types `ls -la /tmp` your shell should run the program `/bin/ls` with the given arguments `-la` and `/tmp`.

## Structure

### Basic Shell

Shell runs in a while loop, and repeatedly asks the user for input to tell it what command to execute.
To read lines, you should use `getline()` 

To parse the input line, you might want to use `strsep()`

To execute commands, use `fork()`, `exec()` and `wait()/waitpid()`

### Paths

The user must specify a path to describe the set of directories to search for executables. In fact, the set of directories that comprise the path are sometimes called the search path of the shell, and it contains the list of all directories to search when a user types a command.

To check if a particular file exists, consider the `access()` system call which you'd run on the paths set by a user. Initially your shell path should contain `/bin`

### Built in Commands

When you get a command, check if it's built in or not. If it's not, you should handle this. There's a few commands to incorporate:

- `exit` which will use the system exit call with 0 as a param
- `cd` this should ALWAYS take only one arg, any more is an error. To change directories, use the `chdir()` system call with the arg supplied. If `chdir` fails, this is an error too.
- `path` this is used with one or more args like `path /bin /usr/bin` which will overwrite the existing path. If the user sets path to be empty, they shouldnt be able to run any programs.

### Redirection

You can use this to put stuff into a file `>` and your shell should handle this.

### Parallel commands

`cmd1 & cmd2` should run `cmd1` and `cmd2` simultaneously with whatever args have been passed. After you've started, make sure to use `wait()` or `waitpid` to wait for them to complete.

### Program errors

You've only got one error, `An error has occurred`. If it's a fatal error, you can show that and `exit(1)` to exit the shell.

### Plan

1) Get basic functionality up, meaning an interactive loop that will store a command and process it (stub processing it...)
2) Create a file that contains the path, read from that on shell init and store that in memory somewhere. 
3) Get a single command, like `ls` running.
4) Add built in commands (exit, cd, path)
5) With path, make sure that we reinit the existing path variable
6) Redirection
7) Parallel commands
8) Deal with varying amounts of white space: ` `, `/t` 
