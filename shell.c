#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_SIZE 4096
#define MAX_ARGS 25
#define MAX_COMMANDS 25
#define MAX_WORD_SIZE 25

struct termios orig_termios;

void disable_raw_mode(void) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode(void) {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &orig_termios);

    // On exit, disable raw mode
    atexit(disable_raw_mode); 

    // Enable raw mode
    raw = orig_termios;
    cfmakeraw(&raw);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// void enable_raw_mode(void) {
//     struct termios termios;
//     tcgetattr(STDIN_FILENO, &termios);
//     cfmakeraw(&termios);
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
// }


enum token_kind { 
    STRING, PIPE, AMPERSAND
};

struct token {
    enum token_kind kind; 
    char *data;
    int length;
};

static bool is_whitespace(char c)
{
	return c == '\t' || c == '\n' || c == '\r' || c == ' ';
}

static bool is_special_char(char c) {
    return c == '&' || c == '|' || c == '>' || c == '<' || c == '(' || c == ')' || c == ';';
}

static bool is_alphabet(char c)
{
	if (c >= 'A' && c <= 'Z') {
		return true;
	}
	else if (c >= 'a' && c <= 'z') {
		return true;
	}
	else {
		return false;
	}
}

static bool is_valid(char c)
{
	return is_alphabet(c) || (c >= '0' && c <= '9') 
        || c == '_' || c == '.' || c == '$' || c == ':' || c == '-' 
        || c == '&' || c == '|' || c == '<' || c == '>' || c == ')'
        || c == '(' || c == '<';
}

void print_string_array(char *arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (i == 0) {
            printf("Printing: ");
        }
        if (arr[i] == NULL) {
            printf("THIS IS NULL ");
        }
        printf("%d: %s, ", i, arr[i]);
    }
    printf("\n");
}

void print_token_array(struct token *lexer[]) {
    for (int i = 0; lexer[i] != NULL; ++i) {
        printf("Type: %d\n\r", lexer[i]->kind);
        if (lexer[i]->kind == 0) {
            printf("String Data: ");
            for (int j = 0; j < lexer[i]->length; ++j) {
                printf("%c", lexer[i]->data[j]);
            }
            printf("\n\r");
        }
        else {
            printf("Other Data: ");
            for (int j = 0; j < lexer[i]->length; ++j) {
                printf("%c", lexer[i]->data[j]);
            }
            printf("\n\r");
        }
        printf("\n\r");
    }
    printf("\n");
}

int num_tokens(char *input_string) {
    // Counts how many seperate words are in the input strings
    int count = 0;

    for (int i = 0;  input_string != NULL && input_string[i] != '\0'; ++i) {
        bool is_word = false;

        while(is_whitespace(input_string[i])) {
            ++i;
        }

        // Check for special characters
        if (is_special_char(input_string[i])) {
            ++count;
            continue;
        }

        while(is_valid(input_string[i])) {
            if (is_special_char(input_string[i])) {
                --i;
                break;
            }
            ++i;
            is_word = true;
        }
        if (is_word) {
            ++count;
        }
    }

    return count;
}

int token_size(char *token) {
    int count = 0;

    for (int i = 0; !is_whitespace(token[i]) && !is_special_char(token[i]) && is_valid(token[i]) && token[i] != '\0'; ++i) {
        ++count;
    }

    return count;
}

/*

If an exec_argv array is implemented:

void free_exec_argv(char** exec_argv) {
    if (exec_argv != NULL) {
        for (int i = 0; exec_argv[i] != NULL; ++i) {
            free(exec_argv[i]);
        }
        free(exec_argv);
    }
}


*/



void free_tokens(struct token *token_array[]) {
    // Token arrays will be NULL terminated
    for (int i = 0; token_array[i] != NULL; ++i) {
        free(token_array[i]->data);
        free(token_array[i]);
    }

    free(token_array);

}



// input_string should have no whitespaces in front or after the string.
// Returns a pointer to the exec_argv array of strings. 

// Points to an array of pointers of token structures
struct token** lexer(char* input_string) { 
    
    // First word in the input is the command 
    bool beginning = true; 
    int size = 0;
    int start_str_index = 0; 
    int current_token = 0;
    bool is_string_token = false;

    // Create the exec_argv array. + 1 added for NULL (last index)
    int token_count = num_tokens(input_string);
    // printf("Num of tokens: %d\n\r", token_count);

    // +1 included for NULL pointer
    // Points to an array of pointers of token structures
    struct token** lexer_array = (struct token**) malloc(sizeof(struct token*) * (token_count + 1)); 
    lexer_array[token_count] = NULL;
    
    for (int i = 0; i < MAX_INPUT_SIZE; ++i) { // OLD CONDITION: && input_string[i] != '\0'

        if (is_whitespace(input_string[i]) && beginning) { 
            start_str_index = i + 1;
            continue;
        }
        beginning = false;

        // Check for special characters
        if (is_special_char(input_string[i]) && !is_string_token) {
            // Single char + null byte
            struct token* temp_token = (struct token*) malloc(sizeof(struct token));
            char* data = (char*) malloc(sizeof(char));
            data[0] = input_string[i];
            switch (input_string[i]) {
                case '|':
                    temp_token->kind = PIPE;
                    break;
            
                case '&':
                    temp_token->kind = AMPERSAND;
                    break;

                // Add any other simple tokens here

                default:
                    perror("ERROR. Unrecongized simple token.");
                    continue;
            }

            temp_token->length = 1;
            temp_token->data = data;
            lexer_array[current_token] = temp_token;

            ++current_token;
            
            start_str_index = i + 1;
            beginning = true;
            continue;
            
        }


        // Whitespaces and \0 indicates the end of an argument
        if (is_whitespace(input_string[i]) || input_string[i] == '\0' || is_special_char(input_string[i])) { 
            // Empty case
            if (start_str_index == i) {
                if (input_string[i] == '\0') {
                    break;
                }
                else {
                    continue;
                }
            }

            char *temp_str = (char *) malloc(sizeof(char) * (token_size(input_string + start_str_index)));
            size = token_size(input_string + start_str_index);
            // printf("Token size: %d\n\r", size);

            // Save characters in temp_str
            for (int j = start_str_index, k = 0; j < start_str_index + size; ++j, ++k) {
                temp_str[k] = input_string[j]; 
            }
            // Null terminate the string
            // temp_str[size] = '\0';

            // Create string struct and add it to lexer_array
            struct token* StringToken = (struct token*) malloc(sizeof(struct token*));
            StringToken->kind = STRING;
            StringToken->data = temp_str;
            StringToken->length = size;
            // printf("[%s]", StringToken->data);


            // Add temp_str pointer to lexer array
            lexer_array[current_token] = StringToken;


            // Reset at the beginning of the next word
            if (is_special_char(input_string[i])) {
                --i;
            }

            beginning = true;
            is_string_token = false;
            start_str_index = i + 1;
            size = 0;
            ++current_token;

            continue;

        }
        is_string_token = true;

    }

    return lexer_array;
}


/*

If exec_argv array is implemented:

// Function to execute process

int execute(char* exec_argv[], pid_t pid){ 

    if (pid < 0) {
        return EXIT_FAILURE;
    }
    
    // This is the child process 
    else if (pid == 0) { 
        // printf("\r\n\r");
        execvp(exec_argv[0], exec_argv);
        perror("\rdish"); // error message

        // The child process should be terminated if execvp fails
        exit(EXIT_FAILURE);
        
    }
    // This is the parent process
    else if (pid > 0) { 

        // Wait for the child process to terminate, then continue
        wait(NULL); 

    }
}

*/


int main(void) {
    enable_raw_mode();

    /*
    If exec_argv array is implemented:
    
    char **exec_argv = NULL; // one reserved for file name, one for NULL pointer)

    */
    char *input = (char *) malloc(sizeof(char) * MAX_INPUT_SIZE);
    int char_index = 0;
    char c = '\0';

    printf("$ ");
    fflush(stdout);

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q' && c != 3) { // CTRL + C also exits program
        
        if (c == '\r' || c == '\n') { // Enter is pressed
            printf("\n\r");

            // Remove end whitespaces
            while(input[char_index - 1] == ' ') {
                --char_index;
            }

            // Null terminate the string
            input[char_index] = '\0';

            struct token** lexer_array = lexer(input);

            /*

            If an exec_argv array is implemented:
            exec_argv = // Assign it here

            */

            print_token_array(lexer_array);
            free_tokens(lexer_array);

            /* 

            If an exec_argv array is implemented:
            
            pid_t pid = fork();
            execute(exec_argv, pid); // Pass in the exec_argv array

            */

            // Reset input and print out starting '$'
            for (int i = 0; i < MAX_INPUT_SIZE; ++i) {
                input[i] = '\0'; //
            }

            char_index = 0;
        
            /*

            If an exec_argv array is implemented:

            // Free the array 
            free_exec_argv(exec_argv);
            exec_argv = NULL;

            */
 

            // printf("\n\r");
            printf("\n\r$ ");

        }
        
        // Backspace key for raw mode
        else if (c == 127 || c == 8){ 
            if (char_index != 0) {
                input[char_index] = '\0';
                --char_index;
                printf("\b \b");
            }
        }

        // Up arrow: \x1b[A
        // Down arrow: \x1b[B
        // Right arrow: \x1b[C
        // Left arrow: \x1b[D
        
        else if (c == 27) { // Escape character
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == 1 && read(STDIN_FILENO, &seq[1], 1) == 1) {
                if (seq[0] == '[') {
                    // Check for arrow keys
                    if (seq[1] == 'A' || seq[1] == 'B' || seq[1] == 'C' || seq[1] == 'D') {
                        // Ignore arrow keys
                        continue;
                    }
                }
            }
        }

        else if (char_index == MAX_INPUT_SIZE - 1){
            printf("\nToo large of an input given.\r\n");
            free(input);
            return EXIT_FAILURE;
        }

        else if (is_valid(c) || c == ' ') {
            input[char_index] = c;
            printf("%c", c);
            ++char_index;
        }
        else {
            // Pass, unknown character
        }

        fflush(stdout); // immediately flush outputs
    }

    free(input);
    /*

    If an exec_argv array is implemented:
    
    // Free the array
    free_exec_argv(exec_argv);

    */

    return 0;
}

