#define PATH_SEPARATOR " \t\r\n"

#include "main.h"

/* Global Variables */
int status = 0;

/**
 * main - Simple shell program
 * @argc: Number of arguments passed to the program
 * @argv: Array of strings representing the arguments passed to the program
 *
 * Description: This function is the entry point for a simple shell program.
 * It creates an infinite loop that prompts the user for input and executes
 * commands entered by the user. The loop continues until the user exits the
 * shell by typing 'exit' or by pressing Ctrl-D. The function prints a prompt
 * 'hsh: $ ' to the standard output using the _write function, reads a line of
 * input from the user using the _getline function, and tokenizes the input
 * using the tokenize function. If the first token is NULL, indicating an empty
 * command, the function frees the tokens array and continues to the next
 * iteration of the loop. If the first token is 'echo $PATH', the function
 * calls the execute_echo_path function. If the first token is 'setenv', the
 * function calls the setenv_command function. If the first token is
 * 'unsetenv', the function calls the unsetenv_command function. If the first
 * token is 'exit', the function calls the execute_exit function with the
 * second token as the argument. Otherwise, the function calls the
 * execute_command function. After executing the command, the function frees
 * the tokens array and repeats the loop. The function also frees the input
 * buffer before exiting.
 *
 * Return: This function returns 0 if the program exits successfully.
 */

int main(int argc, char **argv)
{
	char *buf, *prompt = "hsh: $ ";
	char **tokens;
	int line_number = 1;
	size_t n = 0;
	ssize_t val;
	(void)argc;
	(void)argv;

	buf = NULL;

	if (!isatty(STDIN_FILENO))
	{
		while ((val = getline(&buf, &n, stdin)) != -1)
		{
			tokens = tokenize(buf);
			if (tokens == NULL)
			{
				continue;
			}
			if (_strcmp(tokens[0], "echo") == 0 && _strcmp(tokens[1], "$PATH") == 0)
			{
				execute_echo_path();
			}
			else if (_strcmp(tokens[0], "env") == 0)
			{
				execute_env();
			}
			else if (_strcmp(tokens[0], "exit") == 0)
			{
				status = execute_exit(tokens[1], line_number, argv[0]);
				free(tokens);
				free(buf);
				exit(status);
			}
			else if (_strcmp(tokens[0], "setenv") == 0)
				_setenv(tokens[1], tokens[2]);
			else if (_strcmp(tokens[0], "unsetenv") == 0)
				_unsetenv(tokens[1]);
			else
				execute_command(tokens, line_number, argv[0]);
			free(tokens);
			line_number++;
		}
		free(buf);
	}
	else
	{
		while (1)
		{
			_write(prompt);
			fflush(stdout);
			val = getline(&buf, &n, stdin);
			if (val == -1)
				return (-1);
			tokens = tokenize(buf);
			if (tokens[0] == NULL)
			{
				continue;
			}

			line_number++;
			if (_strcmp(tokens[0], "echo") == 0 && _strcmp(tokens[1], "$PATH") == 0)
			{
				execute_echo_path();
			}
			else if (_strcmp(tokens[0], "env") == 0)
			{
				execute_env();
			}
			else if (_strcmp(tokens[0], "exit") == 0)
			{
				execute_exit(tokens[1], line_number, argv[0]);
				free(tokens);
				free(buf);
				return (0);
			}
			else if (_strcmp(tokens[0], "setenv") == 0)
				_setenv(tokens[1], tokens[2]);
			else if (_strcmp(tokens[0], "unsetenv") == 0)
				_unsetenv(tokens[1]);
			else
				execute_command(tokens, line_number, argv[0]);

			free(tokens);
		}
		free(buf);
	}

	return (0);
}

/**
 * tokenize - Split a string into tokens
 * @input: The string to be tokenized
 *
 * Description: This function receives a string and splits it into tokens based
 * on the delimiters " " and "\n". It uses the _strtok function to do the
 * tokenization and stores the tokens in a dynamically allocated
 * array of strings. The tokens are separated by NULL.
 * The function returns a pointer to the array of strings.
 *
 * Return: A pointer to a dynamically allocated array of strings (tokens).
 * If there is a memory allocation error, the function returns NULL.
 */
char **tokenize(char *input)
{
	char **tokens = malloc(BUFSIZE * sizeof(char *));
	char *token;
	int i;

	i = 0;
	if (!tokens)
	{
		perror("Memory allocation error");
		free(tokens);
		exit(EXIT_FAILURE);
	}

	token = strtok(input, PATH_SEPARATOR);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, PATH_SEPARATOR);
	}

	tokens[i] = NULL;
	if (i == 0)
	{
		free(tokens);
		tokens = NULL;
	}
	return (tokens);
}
