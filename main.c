#define PATH_SEPARATOR " \t\r\n"

#include "main.h"

/* Global Variables */
int status = 0;

/**
 * execute_shell_command - Execute a shell command based on the given tokens
 * @tokens: Array of strings representing the command tokens
 * @line_number: Line number of the command in the input
 * @program_name: Name of the shell program
 *
 * Description: This function takes an array of strings representing command
 * tokens and executes the appropriate shell command based on the first token.
 * If the first token is 'echo $PATH', it calls the execute_echo_path function.
 * If the first token is 'env', it calls the execute_env function. If the first
 * token is 'exit', it calls the execute_exit function with the second token
 * as the argument. If the first token is 'setenv', it calls the _setenv
 * function. If the first token is 'unsetenv', it calls the _unsetenv function.
 * Otherwise, it calls the execute_command function to execute a generic
 * command. The function returns 1 if the command execution is successful,
 * and 0 if the command is 'exit', indicating that the shell should exit.
 *
 * Return: 1 for successful command execution, 0 for 'exit' command.
 */

int execute_shell_command(char **tokens, int line_number, char *program_name)
{
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
		execute_exit(tokens[1], line_number, program_name);
		free(tokens);
		exit(status);
	}
	else if (_strcmp(tokens[0], "setenv") == 0)
	{
		_setenv(tokens[1], tokens[2]);
	}
	else if (_strcmp(tokens[0], "unsetenv") == 0)
	{
		_unsetenv(tokens[1]);
	}
	else
	{
		execute_command(tokens, line_number, program_name);
	}

	return (0);
}

/**
 * process_input - Process input from the command line
 * @buf: Input buffer
 * @prompt: Prompt string
 * @program_name: Name of the shell program
 *
 * Description: This function processes input from the command line in an
 * interactive mode. It displays the prompt string, reads a line of input
 * using the _getline function, tokenizes the input using the tokenize
 * function, and executes the shell command based on the tokens using the
 * execute_shell_command function. If the first token is NULL, indicating an
 * empty command, the function continues to the next iteration. The function
 * repeats this process until the user exits the shell by typing 'exit' or
 * pressing Ctrl-D. The function frees the tokens array after executing each
 * command, and frees the input buffer before returning.
 */
void process_input(char *buf, char *prompt, char *program_name)
{
	char **tokens;
	int line_number = 1;
	size_t n = 0;
	ssize_t val;

	while (1)
	{
		_write(prompt);
		fflush(stdout);
		val = getline(&buf, &n, stdin);
		if (val == -1)
			return;

		tokens = tokenize(buf);
		if (tokens[0] == NULL)
		{
			continue;
		}

		line_number++;
		if (!execute_shell_command(tokens, line_number, program_name))
		{
			free(tokens);
			free(buf);
			return;
		}
		free(buf);
		free(tokens);
	}
	free(buf);
}

/**
 * process_file_input - Process input from a file
 * @buf: Input buffer
 * @program_name: Name of the shell program
 *
 * Description: This function processes input from a file. It reads lines of
 * input from the file using the _getline function, tokenizes each line using
 * the tokenize function, and executes the shell command based on the tokens
 * using the execute_shell_command function. If the first token is NULL,
 * indicating an empty command, the function continues to the next line. The
 * function repeats this process until the end of the file. The function frees
 * the tokens array after executing each command, and frees the input buffer
 * before returning.
 */
void process_file_input(char *buf, char *program_name)
{
	char **tokens;
	int line_number = 1;
	size_t n = 0;
	ssize_t val;

	while ((val = getline(&buf, &n, stdin)) != -1)
	{
		tokens = tokenize(buf);
		if (tokens == NULL)
		{
			continue;
		}

		if (!execute_shell_command(tokens, line_number, program_name))
		{
			free(tokens);
			free(buf);
			exit(status);
		}

		free(tokens);
		line_number++;
	}

	free(buf);
}

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
 * calls the execute_echo_path function. If the first token is 'env', the
 * function calls the execute_env function. If the first token is 'exit', the
 * function calls the execute_exit function with the second token as the
 * argument. If the first token is 'setenv', the function calls the _setenv
 * function. If the first token is 'unsetenv', the function calls the _unsetenv
 * function. Otherwise, the function calls the execute_command function. After
 * executing the command, the function frees the tokens array and repeats the
 * loop. The function also frees the input buffer before exiting.
 *
 * Return: This function returns 0 if the program exits successfully.
 */
int main(int argc, char **argv)
{
	char *buf;
	char *prompt = "hsh: $ ";

	(void)argc;
	(void)argv;

	buf = NULL;

	if (!isatty(STDIN_FILENO))
	{
		process_file_input(buf, argv[0]);
	}
	else
	{
		process_input(buf, prompt, argv[0]);
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
