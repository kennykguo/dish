#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

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
    enable_raw_mode();
    char c;
    int index = 0;
    // Reads from the std input. If function returns 1, then the character was successfully read.
    // read will constantly read a character
    while (true){
        if (read(STDIN_FILENO, &c, 1) != 1 || c == ' ' || c == '\t' || c == '\n' || c == 'q') {
            
        }
    }

    return 0;
}

