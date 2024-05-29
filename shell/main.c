#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void enable_raw_mode(void) {
    struct termios termios;
    tcgetattr(STDIN_FILENO, &termios);
    cfmakeraw(&termios);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

#define MAX_INPUT_SIZE 4096
#define MAX_ARGS 128

int main(void) {
    // Raw mode is a mode where the terminal does not perform any processing or handling of the input and output.
    // enable_raw_mode();

    char c = '\0';
    int commandsIndex = 0;
    int stringIndex = 0;
    // May need to point all char* to NULL
    char** commands = (char**)malloc(MAX_ARGS * sizeof(char*));
    // Reads from the std input. If function returns 1, then the character was successfully read.
    // read will constantly read a character
    // TODO: Figure out a way to constantly read and take in commands - when user hits enter, we know that we should stop reading for the full command
    // After enter, we should reset an index
    while (1){
        // Allocate memory for string at corresponding index
        *(commands + commandsIndex) =(char*) malloc(MAX_INPUT_SIZE * sizeof(char));
        // Loop will continue reading until
        while (1)
        {
            // Read characters until invalid input, or user presses enter
            read(STDIN_FILENO, &c, 1);
            // User presses enter
            if (commandsIndex >= MAX_ARGS){
                printf("invalid number of commands");
                break;
            }
            if (stringIndex >= MAX_INPUT_SIZE){
                printf("invalid command length");
                break;
            }
            if (c == '\n'){
                *(*(commands + commandsIndex) + stringIndex) = '\n';
                // Break out immediately ->
                break;
            }
            // User presses space -> break out of loop
            else if (c == ' '){
                *(*(commands + commandsIndex) + stringIndex) = '\n';
                commandsIndex++;
                stringIndex = 0;
                break;
            }
            else{
                // Access the correct string. Access the correct index of the correct string. Add the corresponding character
                *(*(commands + commandsIndex) + stringIndex) = c;
                stringIndex++;
            }
        }
        // Check if user last pressed enter. If so, then execute the corresponding command
        if (*(*(commands + commandsIndex) + stringIndex) == '\n'){
            commandsIndex = 0;
            stringIndex = 0;
            if (strncmp(*(commands), "exit", 4) == 0 && *(commands) == NULL){
                break;
            }
            else
            {
                printf("command does not exist, or invalid command :(");
            }
        }
        // If user reached maximum args, or maximum arg length
        else
        {
            commandsIndex = 0;
            stringIndex = 0;
        }
        // When done, free all pointers and point them to NULL for the next array of commands
        for (int index = 1; index< MAX_ARGS; index++){
            free(commands + index);
            *(commands + index) = NULL;
        }
    }
    printf("shell is exiting");
    return 0;
}

