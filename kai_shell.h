#ifndef KAI_SHELL_H
#define KAI_SHELL_H

// Function prototypes for built-in commands
extern char *builtin_str[];
extern int (*builtin_func[])(char **);

int kai_num_builtins(void);
int kai_cd(char **args);
int kai_help(char **args);
int kai_exit(char **args);
int kai_hello(char **args); // New function prototype for hello command
int kai_date(char **args); // New function prototype for date command

#endif  // KAI_SHELL_H