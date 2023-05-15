#include "main.h"

int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	char *buf[BUFSIZE];
	char **tokens;
	size_t n = 0;
	ssize_t val;
	(void)argc;
	(void)argv;

	/* create an infinite loop */
	while (1)
	{
		printf("%s", prompt);
		val = getline(&buf, &n, stdin);
		if (val == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}

		tokens = tokenize(buf);
		if (tokens[0] == NULL)
			continue;

		execute_command(tokens);

		free(tokens);
	}
	return (0);
}

/**
 * tokenize - Split a string into tokens
 * @input: The string to be tokenized
 *
 * Description: This function receives a string and splits it into tokens based on
 * the delimiters " " and "\n". It uses the strtok function to do the tokenization
 * and stores the tokens in a dynamically allocated array of strings. The tokens are
 * separated by NULL. The function returns a pointer to the array of strings.
 *
 * Return: A pointer to a dynamically allocated array of strings (tokens). If there
 * is a memory allocation error, the function returns NULL.
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
		return (-1);
	}

	token = strtok(input, " \n");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}

	tokens[i] = NULL;
	return (tokens);
}

/**
 * execute_command - Execute a command in a new process
 * @tokens: A pointer to an array of strings (tokens) representing the command and its arguments
 *
 * Description: This function receives an array of strings representing a command and its arguments,
 * checks if the command exists, and executes it in a new process using the execv system call. If
 * the command does not exist, the function prints an error message and returns. If there is an
 * error in forking a new process or executing the command, the function prints an error message
 * and exits. The function waits for the child process to complete before returning.
 *
 * Return: This function does not return a value.
 */
void execute_command(char **tokens)
{
	pid_t pid;

	if (access(tokens[0], F_OK) == -1)
	{
		printf("%s : command not found\n", tokens[0]);
		return;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execv(tokens[0], tokens) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		wait(NULL);
	}
}
