# dish

Dish (dope interactive shell) is a basic custom shell in C, providing features such as raw mode input handling, tokenizing input strings, and executing basic commands. The shell supports pipes (`|`) and background execution (`&`).

## Key Components

1. **Initialization and Raw Mode**
   - Enables raw mode for character-by-character input processing
   - Allocates memory for input string
   - Initializes variables for input tracking

2. **Main Function**
   - Processes input into a single string
   - Handles program exit safely without memory leaks

3. **Lexer**
   - Breaks input into tokens
   - Handles spaces and special characters
   - Returns a null-terminated array of token structures

4. **Execute Function**
   - Creates new processes using fork()
   - Runs commands using execvp()
   - Handles parent and child processes

5. **Input Processing**
   - Handles Enter key for command execution
   - Manages backspace for input editing
   - Ignores arrow keys to prevent errors

6. **Error Handling**
   - Checks for maximum input size
   - Provides error messages for invalid inputs

7. **Cleanup**
   - Frees allocated memory before program exit

## Features

- Raw mode input handling
- Tokenizing input strings
- Executing basic commands
- Piping support
- Background execution support

## Potential Improvements

1. Enhanced keyboard functionality (e.g., arrow key navigation)
2. Implementation of a linked list for input tracking
3. Additional built-in commands
4. Command history functionality

## Code Structure

The program is divided into several key functions:

- `enable_raw_mode()`: Sets up the terminal for raw input
- `num_tokens()`: Counts the number of tokens in the input
- `tokenize()`: Breaks the input into tokens
- `execute()`: Creates new processes and runs commands
- Main loop: Handles input processing and command execution

The shell provides a basic but functional command-line interface, with room for further enhancements and features.