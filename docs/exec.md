# The Execute Function

## Understanding Process Creation and Forking

*See lines 319-342*.

The `execute` function is a crucial part of our shell program. It's responsible for creating new processes and running commands. Let's break down its functionality:

```c
int execute(char* exec_argv[], pid_t pid) {
    if (pid < 0) {
        return EXIT_FAILURE;
    }
    else if (pid == 0) {
        execvp(exec_argv[0], exec_argv);
        perror("\rdish");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) {
        wait(NULL);
    }
}

```

# What is a PID?
PID stands for Process ID. It's a unique identifier assigned to each process in an operating system. When a new process is created, the system assigns it a PID.

## How Forking Works
Forking is a way to create a new process. When a process forks, it creates an exact copy of itself. The original process is called the parent, and the new process is called the child. Both processes will continue running from the point where the fork occurred.
Understanding PID Values

If pid < 0: This indicates an error occurred during the fork operation.
If pid == 0: This means we're in the child process.
If pid > 0: This means we're in the parent process, and the value of pid is the PID of the child process.

## The `execvp()` Function
`execvp` is part of the exec family of functions. It replaces the current process image with a new process image. Here's what it does:

The first argument is the name of the program to run.
The second argument is an array of strings representing the command-line arguments.

If execvp fails, it returns to the calling process and sets errno. That's why we call perror and exit after execvp - these lines will only be reached if execvp fails.

### The Parent Process
In the parent process, we use wait(NULL) to wait for the child process to terminate before continuing. This ensures that the shell doesn't prompt for the next command until the current command has finished executing.

## Future Implementation
If an `exec_argv` array were to be implemented, feel free to uncomment the sections labelled with the following:
```
/*
If exec_argv array is implemented:

// Code

*/

```

This includes functions `execute()` and `free_exec_argv()`.


