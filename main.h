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
void execute_command(char **tokens, int line_number, char *program_name);
char *search_path(char **tokens);
void execute_exit(char *argument);
void execute_echo_path(void);
ssize_t _write(const char *str);
int _strcmp(const char *s1, const char *s2);
const char *_strchr(const char *s, char c);
char *_strdup(const char *str);
int _strlen(const char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memcpy(char *dest, char *src, unsigned int n);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
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
int _validate_setenv_input(const char *name, const char *value);
int _setenv(const char *name, const char *value);
char *_strcpy(char *dest, char *src);
int _replace_env_variable(const char *name, char *new_env);
void _append_env_variable(char **new_environ, char *new_env);
size_t _get_environ_size(void);
void _shift_env_pointers(char **env, size_t index);
int _unsetenv(const char *name);

#endif /* MAIN_H */
