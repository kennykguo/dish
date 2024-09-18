# Lexer

*See lines 195-310*.

The lexer in this program is used to break the input into their respective tokens. The function returns a null terminated array of pointers belonging to token structures. This lexer first counts the number of tokens (using `num_tokens()`) in order to allocate the appropriate amount of memory, remembering to include the null byte. 

This shell implementation assumes that tokens can only be separated by spaces or special characters. Hence, `ls | wc` and `ls|wc` are still tokenized the same. Using this logic, the input is broken-up into their respective tokens and stored in memory.

