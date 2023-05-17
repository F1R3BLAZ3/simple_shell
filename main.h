#ifndef MAIN_H
#define MAIN_H

#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#define BUFSIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

char **tokenize(char *input);
void execute_command(char **tokens);
char *search_path(char **tokens);

#endif /* MAIN_H */
