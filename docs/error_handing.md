# Error Handling
*See lines 447-451*.

```c
else if (char_index == MAX_INPUT_SIZE - 1) {
    printf("\nToo large of an input given.\r\n");
    free(input);
    return EXIT_FAILURE;
}
```

- Checks if the input has reached the maximum allowed size. If so, it prints an error message and exits.
