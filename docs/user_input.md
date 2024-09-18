# Reading User Input
*See lines 363 and onwards*.

```c
while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q' && c != 3) {
    // ... (rest of the code)
}
```

- This loop reads input one character at a time until the user presses 'q' or Ctrl+C (ASCII value 3).
- read() is used instead of scanf() or getchar() because we're in raw mode.

### Why Use fflush?
fflush(stdout): Ensures that any buffered output is immediately written to the console. This is crucial in raw mode, where normal line buffering is disabled.

