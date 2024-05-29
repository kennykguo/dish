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
    for (int index = 0; index < MAX_ARGS; index++) {
        *(commands + index) = NULL;
    }
    printf("starting shell\n");

    while (true) {
        printf("$ ");
        fflush(stdout); 

        // Allocate memory for string at corresponding index
        *(commands + commandsIndex) = (char*)malloc(MAX_INPUT_SIZE * sizeof(char));
        
        // Loop will continue reading until enter or space is pressed by the user
        printf("reached 1\n");
        
        // Read characters until invalid input, or user presses enter
        while (true){
            if (read(STDIN_FILENO, &c, 1) == 1) {
                // Break out of the loop if Enter is pressed
                if (c == ' ') {
                    printf("exiting inner loop %c\n", c);
                    break;
                }
                if (c == 'q') {
                    printf("exiting outer loop %c\n", c);
                    break;
                }
                printf("reading %c\n", c);
                fflush(stdout); 

            } 
        }
        if (c == 'q'){
            break;
        }
    }

    return 0;
}
