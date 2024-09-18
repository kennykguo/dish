# Handling Backspace
*See lines 421-427*.
```c
else if (c == 127 || c == 8) { 
    if (char_index != 0) {
        input[char_index] = '\0';
        --char_index;
        printf("\b \b");
    }
}
```

- ASCII 127 and 8 both represent backspace on different systems.
- Backspace is allowed only if not at the start of the input (char_index != 0).
- The cursor moves back, a space is printed to erase the character, then the cursor moves back again.