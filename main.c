#define PATH_SEPARATOR " \t\r\n"

#include "main.h"

/**
 * main - Simple shell program
 * @argc: Number of arguments passed to the program
 * @argv: Array of strings representing the arguments passed to the program
 *
 * Description: This function is the entry point for a simple shell program.
 * It creates an infinite loop that prompts the user for input
 * and executes commands entered by the user. The loop continues until
 * the user exits the shell by typing 'exit' or by pressing Ctrl-D.
 * The function prints a prompt 'hsh: $ ' to the standard output,
 * reads a line of input from the user using the getline function,
 * and tokenizes the input using the tokenize function.
 * If the first token (command) is 'exit', the function returns.
 * If the first token is NULL, the function continues to the next iteration of
 * the loop. Otherwise, the function executes the command using the
 * execute_command function. The function then frees the memory used
 * by the tokens array and repeats the loop.
 *
 * Return: This function returns 0 if the program exits successfully.
 */
int main(int argc, char **argv)
{
	char *buf, *prompt = "hsh: $ ";
	char **tokens;
	ssize_t val;
	(void)argc;
	(void)argv;

	/* create an infinite loop */
	while (1)
	{
		_write(prompt);
		fflush(stdout);
		val = getline(&buf, &(size_t){0}, stdin);
		if (val == -1)
		{
			_write("Exiting shell..\n");
			return (-1);
		}
		tokens = tokenize(buf);
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}

		if (_strcmp(tokens[0], "echo") == 0 && _strcmp(tokens[1], "$PATH") == 0)
			execute_echo_path();
		else if (_strcmp(tokens[0], "exit") == 0)
			execute_exit();
		else
			execute_command(tokens);
		free(tokens);
	}
	free(buf);
	return (0);
}

/**
 * tokenize - Split a string into tokens
 * @input: The string to be tokenized
 *
 * Description: This function receives a string and splits it into tokens based
 * on the delimiters " " and "\n". It uses the strtok function to do the
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
	return (tokens);
}
