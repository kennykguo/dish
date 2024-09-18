# Tokens
Tokens are data structure that store three pieces of data:
1. The type of token
2. A pointer to an array of characters 
3. The length of the token (or the number of total characters)

When a user gives an input, the shell break up the messy input string into smaller pieces (tokens) that the shell can work with. In this program, you can easily add your own simple tokens (single character tokens) through the following steps:

1. In the enum `token_kind`, add the name of your simple token.
2. In the switch case located in `lexer()`, add a case for the simple token.
3. In `is_special_char()`, add your simple token in the return statement. 

The shell now recongnizes when your simple token is passed in the input. For example, the input 
```
ls | wc
``` 
separates "ls", "|", and "wc" into their separate tokens respectively. 

### Token-related Functions
`print_token_array()`, `num_tokens()`, `token_size()`, ...

