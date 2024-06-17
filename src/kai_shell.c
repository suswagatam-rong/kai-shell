/***************************************************************************//**
  @file         kai_shell.c
  @brief        Implementation of built-in commands for Kai-shell
*******************************************************************************/

#include "kai_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // For date command

// Array of built-in command names
char *builtin_str[] = {
        "cd",
        "help",
        "exit",
        "hello",
        "date" // Include new command in the list
};

// Array of pointers to functions corresponding to built-in commands
int (*builtin_func[]) (char **) = {
        &kai_cd,
        &kai_help,
        &kai_exit,
        &kai_hello,
        &kai_date // Add function pointer for date command
};

// Number of built-in commands
int kai_num_builtins(void) {
    return sizeof(builtin_str) / sizeof(char *);
}

// Built-in command: hello
int kai_hello(char **args)
{
    printf("Hello! Welcome to Kai's Custom Shell!\n");
    return 1;
}

// Built-in command: date
int kai_date(char **args)
{
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current date and time: %s", asctime(timeinfo));

    return 1;
}