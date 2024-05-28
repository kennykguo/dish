// Shell.

#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Parsed command representation
#define EXEC  1
#define REDIR 2
#define PIPE  3
#define LIST  4
#define BACK  5

int main() {
    // Simple shell loop
    char buffer[1024];
    while (1) {
        printf("$ ");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
        // Process the input command (tokenize, fork, exec, etc.)
        printf("You entered: %s", buffer);
    }
    return 0;
}