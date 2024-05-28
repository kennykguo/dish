#include <termios.h>
#include <unistd.h>

void enable_raw_mode(void) {
    struct termios termios;
    tcgetattr(STDIN_FILENO, &termios);
    cfmakeraw(&termios);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

int main(void) {
    enable_raw_mode();
    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}

