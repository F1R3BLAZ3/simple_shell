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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/* Function Declarations */
char **tokenize(char *input);
void execute_command(char **tokens);
char *search_path(char **tokens);
void execute_exit(void);
void execute_echo_path(void);
ssize_t _write(const char *str);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
char *_strdup(char *str);
int _strlen(char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
ssize_t _getline(char **buf, size_t *n, FILE *stream);


#endif /* MAIN_H */
