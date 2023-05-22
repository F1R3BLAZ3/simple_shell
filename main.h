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
void execute_exit(char *argument);
void execute_echo_path(void);
ssize_t _write(const char *str);
int _strcmp(const char *s1, const char *s2);
const char *_strchr(const char *s, char c);
char *_strdup(const char *str);
int _strlen(const char *s);
int read_data(char *buffer, int remaining, FILE *stream);
char *process_buffer(char *str, char *buffer, int bytesRead);
char *_fgets(char *str, int size, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
ssize_t _getline(char **buf, size_t *n, FILE *stream);
ssize_t read_line(char **buf, size_t *n, FILE *stream);
ssize_t extend_buffer(char **buf, size_t *n, size_t new_size);
ssize_t read_remaining(char **buf, size_t *n, FILE *stream, size_t len);
int _atoi(char *str, int n);
int setenv_command(char **tokens);
int unsetenv_command(char **tokens);
unsigned int check_delim(char c, char *delim);
char *_strtok(char *str, char *delim);
char *_getenv(const char *name);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif /* MAIN_H */
