# Processing the Enter Key
*See lines 365-416*.
```c
if (c == '\r' || c == '\n') {
    printf("\n\r");
    // Remove end whitespaces
    while(input[char_index - 1] == ' ') {
        --char_index;
    }
    // Null terminate the string
    input[char_index] = '\0';
    // ... (lexer and execution code)
    // Reset input and print out starting '$'
    for (int i = 0; i < MAX_INPUT_SIZE; ++i) {
        input[i] = '\0';
    }
    char_index = 0;
    printf("\n\r$ ");
}
```

When the user presses enter:
- Trailing whitespaces are removed.
- The input string is null-terminated.
- The input is processed (lexical analysis and execution).
- The input buffer is reset for the next command.
- A new prompt is printed.