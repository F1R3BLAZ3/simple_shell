#ifndef MAIN_H
#define MAIN_H

/* Macro Defines*/
#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#define BUFSIZE 1024

/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* Function Declarations */
int main(void);
char **split_command(char *command);
void execute_command(char *command);
int count_tokens(char *command);

#endif /* MAIN_H */
