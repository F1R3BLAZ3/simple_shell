#define PATH_SEPARATOR " \t\r\n"

#include "main.h"

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
	char *prompt = "hsh: $ ";
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	(void)argc;
	(void)argv;

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			_write(prompt);

			read = _getline(&line, &len, stdin);

			if (read == -1)
			{
				_write("\n");
				break;
			}

			if (read > 0 && line[read - 1] == '\n')
				line[read - 1] = '\0';

			execute_command(tokenize(line));
		}
	}
	else
	{
		read = _getline(&line, &len, stdin);

		if (read > 0 && line[read - 1] == '\n')
			line[read - 1] = '\0';

		execute_command(tokenize(line));
		_write(prompt);
	}

	free(line);
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
		perror(tokens[0]);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, PATH_SEPARATOR);
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		i++;
		token = _strtok(NULL, PATH_SEPARATOR);
	}

	tokens[i] = NULL;
	return (tokens);
}
