# Handling Valid Characters

*See lines 453-457*.

```c
else if (is_valid(c) || c == ' ') {
    input[char_index] = c;
    printf("%c", c);
    ++char_index;
}
else {
    pass
}
```

- Valid characters are added to the input buffer and unknown characters are ignored.