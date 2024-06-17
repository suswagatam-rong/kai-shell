/***************************************************************************//**
  @file         main.c
  @brief        Main entry point for Kai-shell
*******************************************************************************/

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "kai_shell.h"

/*
  Builtin function implementations.
*/

// Built-in command: change directory
int kai_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "kai-shell: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("kai-shell");
        }
    }
    return 1;
}

// Built-in command: print help
int kai_help(char **args)
{
    int i;
    printf("Welcome to Kai's Custom Shell\n");
    printf("Available commands:\n");

    for (i = 0; i < kai_num_builtins (); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    return 1;
}

// Built-in command: exit shell
int kai_exit(char **args)
{
    return 0;
}

// Launch a program and wait for it to terminate
int kai_launch(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("kai-shell");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("kai-shell");
    } else {
        // Parent process
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

// Execute shell built-in or launch program
int kai_execute(char **args)
{
    int i;

    if (args[0] == NULL) {
        // An empty command was entered
        return 1;
    }

    // Check if the command is a built-in command and execute it
    for (i = 0; i < kai_num_builtins (); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    // If the command is not a built-in, launch it as a separate process
    return kai_launch (args);
}

// Read a line of input from stdin
char *kai_read_line(void)
{
#define KAI_RL_BUFSIZE 1024
    int bufsize = KAI_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "kai-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate
        if (position >= bufsize) {
            bufsize += KAI_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "kai-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

#define KAI_TOK_BUFSIZE 64
#define KAI_TOK_DELIM " \t\r\n\a"

// Split a line into tokens
char **kai_split_line(char *line)
{
    int bufsize = KAI_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        fprintf(stderr, "kai-shell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, KAI_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        // If we exceed the buffer, reallocate
        if (position >= bufsize) {
            bufsize += KAI_TOK_BUFSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "kai-shell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, KAI_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// Main command loop
void kai_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("kai-shell> ");
        line = kai_read_line (); // Read input
        args = kai_split_line (line); // Split input into arguments
        status = kai_execute (args); // Execute command

        free(line);
        free(args);
    } while (status);
}

// Main function
int main(int argc, char **argv)
{
    kai_loop (); // Run command loop

    return EXIT_SUCCESS;
}