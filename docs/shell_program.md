---
id: shell-program
title: Custom Shell Program
sidebar_position: 1
---

# Custom Shell Program

## Overview

This project implements a basic custom shell in C. The shell provides features such as:

- Raw mode input handling
- Tokenizing input strings
- Handling basic commands like pipes (`|`) and ampersands (`&`)

## Features

### Raw Mode

The shell operates in raw mode, allowing for character-by-character input processing. This is useful for handling special characters and creating a responsive command-line interface.

### Tokenizing Input

The input string is tokenized into commands and arguments. The tokenizer recognizes special characters like `|` (pipe) and `&` (ampersand) and separates them into individual tokens.

### Command Execution

The shell can execute basic commands using `execvp`. It supports piping and background execution using the `fork()` system call.

### Main Function
Responsible for processing the input into a single string. It also allows the user to exit the program safely without memory leaks.

<!-- ```c
int main(void) {
    enable_raw_mode();
    char **exec_argv = NULL;
    char *input = (char *) malloc(sizeof(char) * MAX_INPUT_SIZE);
    int char_index = 0;
    char c = '\0';

    printf("$ ");
    fflush(stdout);

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q' && c != 3) {
        // Processing input and handling commands
    }

    free(input);
    return 0;
} -->
