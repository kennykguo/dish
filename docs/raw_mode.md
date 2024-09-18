# Raw Mode
Raw mode allows the shell to take input continuously. Every keystroke is taken literally (for example, backspace won't actually work as a backspace but will be taken as the key 127). This can be useful if you're planning to implement autocorrect or spell check in your program. As it is currently set up, it saves the original configuration of the shell before entering raw mode. Before the program exits, it returns to the original saved state.

## Smaller Helper Functions
`is_whitespace()` , `is_special_char()`, `is_alphabet()`, `is_valid()`, `print_string_array()`, ... 

The above functions are self explainatory, but they help simplify the code.

