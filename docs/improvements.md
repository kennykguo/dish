# Improving the Shell Application

This page outlines potential improvements and additional features that could be implemented in our shell program. These enhancements would provide valuable learning experiences in various aspects of operating systems and programming.

1. Improve keyboard functionality.

Currently, arrow keys are disabled, so it is not possible to navigate between characters to edit a word. Instead of the current input system, a linked list can be created to keep track of the cursor position, where the left and right arrow keys can navigate between each node in the list. If a valid character is pressed, a character node can be appended to the node selected by the cursor. After the user presses Return/Enter, the linked list is converted into a single string as input for the lexer.
<!-- 2. Create the following function: `char** token_array_to_argv(struct **token_array)` -->