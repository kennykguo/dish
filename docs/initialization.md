# Initialization and Raw Mode
*See lines 14-32*.
```c
enable_raw_mode();
char **exec_argv = NULL;
char *input = (char *) malloc(sizeof(char) * MAX_INPUT_SIZE);
int char_index = 0;
char c = '\0';
```

#### `enable_raw_mode()`: 
Sets up the terminal for raw input, allowing us to read input character by character. This allows us to have full control of the output. As a result, `printf(\n<Message>)` **may not** reguarly print a message at the beginning of the next line. Instead, we should use `printf(\n\r<Message>)`, where `\r` is the carriage return character. For example,

Without carriage return:
```
printf("This is ECE344\nWelcome!");
```
>Output:
```
This is ECE344
              Welcome!
```

With carriage return:

```
printf("This is ECE344\n\rWelcome!");
```
>Output:

```
This is ECE344
Welcome!
```

- Memory is allocated for the input string, and variables are initialized for tracking the input.




