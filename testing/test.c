#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    // Raw mode is a mode where the terminal does not perform any processing or handling of the input and output.
    char c;
    read(STDIN_FILENO, &c, 1);
    printf("%c", c);
    return 0;
}
