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
    
    // Allocate memory for the commands array and point them to NULL
    char** commands = (char**)malloc(MAX_ARGS * sizeof(char*));
    for (int index = 0; index< MAX_ARGS; index++){
         *(commands + index) = NULL;
    }
    // Reads from the std input. If function returns 1, then the character was successfully read.
    // read will constantly read a character
    // TODO: Figure out a way to constantly read and take in commands - when user hits enter, we know that we should stop reading for the full command
    // After enter, we should reset an index
    printf("starting shell\n");

    while (true){
        printf("$ ");
        fflush(stdout); 
        // Allocate memory for string at corresponding index
        *(commands + commandsIndex) =(char*) malloc(MAX_INPUT_SIZE * sizeof(char));
        
        // Loop will continue reading until enter or space is pressed by the user
        while (true)
        {
            // Read characters until invalid input, or user presses enter
            if (read(STDIN_FILENO, &c, 1) == 1) {
                printf("reading %c\n", c);
                fflush(stdout); 

                // Break out of the loop if Enter is pressed
                if (c == '\n' || c == ' ') {
                    break;
                }
            } 
            else 
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            // Invalid argument number
            if (commandsIndex >= MAX_ARGS - 1) {
                printf("Invalid number of commands\n");
                break;
            }

            // Invalid argument length
            if (stringIndex >= MAX_INPUT_SIZE - 1) {
                printf("Invalid command length\n");
                break;
            }

            // User presses enter
            if (c == '\r'){
                commands[commandsIndex][stringIndex] = '\0';
                break;
            }

            // User presses space -> break out of loop
            else if (c == ' '){
                commands[commandsIndex][stringIndex] = '\0';
                commandsIndex++;
                stringIndex = 0;
                break;
            }

            // Access the correct string. Access the correct index of the correct string. Add the corresponding character
            else{
                *(*(commands + commandsIndex) + stringIndex) = c;
                stringIndex++;
            }
        }

        // Check if user last pressed enter. If so, then execute the corresponding command
        if (commands[commandsIndex][stringIndex]== '\n'){
            commandsIndex = 0;
            stringIndex = 0;
            if (strcmp(commands[0], "exit") == 0){
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
        for (int index = 0; index <= commandsIndex; index++) {
            free(commands[index]);
            commands[index] = NULL;
        }
        
        commandsIndex = 0;
    }

    for (int index = 0; index <= commandsIndex; index++) {
        free(commands[index]);
        commands[index] = NULL;
    }
    free(commands);
    printf("shell is exiting\n");
    fflush(stdout); 
    return 0;
}

