#define PATH_SEPARATOR " \t\r\n"

#include "main.h"

/* Global Variables */
int status = 0;


void noninteractive_mode(char *program_name)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t val;
	char **tokens;
	int line_number = 1, status;

	while ((val = getline(&buf, &n, stdin)) != -1)
	{
		tokens = tokenize(buf);
		if (tokens == NULL)
			continue;

		if (strcmp(tokens[0], "echo") == 0 && strcmp(tokens[1], "$PATH") == 0)
			execute_echo_path();
		else if (strcmp(tokens[0], "env") == 0)
			execute_env();
		else if (strcmp(tokens[0], "exit") == 0)
		{
			status = execute_exit(tokens[1], line_number, program_name);
			free(tokens);
			free(buf);
			exit(status);
		}
		else if (strcmp(tokens[0], "setenv") == 0)
			_setenv(tokens[1], tokens[2]);
		else if (strcmp(tokens[0], "unsetenv") == 0)
			_unsetenv(tokens[1]);
		else
			execute_command(tokens, line_number, program_name);

		free(tokens);
		line_number++;
	}
	free(buf);
}

void interactive_mode(char *prompt, char *program_name)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t val;
	char **tokens;
	int line_number = 1;

	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);
		val = getline(&buf, &n, stdin);
		if (val == -1)
			break;
		tokens = tokenize(buf);
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
		line_number++;
		if (strcmp(tokens[0], "echo") == 0 && strcmp(tokens[1], "$PATH") == 0)
			execute_echo_path();
		else if (strcmp(tokens[0], "env") == 0)
			execute_env();
		else if (strcmp(tokens[0], "exit") == 0)
		{
			execute_exit(tokens[1], line_number, program_name);
			free(tokens);
			break;
		}
		else if (strcmp(tokens[0], "setenv") == 0)
			_setenv(tokens[1], tokens[2]);
		else if (strcmp(tokens[0], "unsetenv") == 0)
			_unsetenv(tokens[1]);
		else
			execute_command(tokens, line_number, program_name);
		free(tokens);
	}
	free(buf);
}

int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	(void)argc;

	if (!isatty(STDIN_FILENO))
	{
		noninteractive_mode(argv[0]);
	}
	else
	{
		interactive_mode(prompt, argv[0]);
	}

	return 0;
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
