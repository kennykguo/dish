
# Handling Arrow Keys

*See lines 434-445*.

```c
else if (c == 27) { // Escape character
    char seq[2];
    if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
        if (seq[0] == '[') {
            // Check for arrow keys
            if (seq[1] == 'A' || seq[1] == 'B' || seq[1] == 'C' || seq[1] == 'D') {
                // Ignore arrow keys
                continue;
            }
        }
    }
}
```



Arrow keys send a sequence of characters:
- Escape character (27)
- '['
- 'A', 'B', 'C', or 'D' for up, down, right, or left respectively

These characters are read and ignored to prevent the user from causing an error in the shell.
