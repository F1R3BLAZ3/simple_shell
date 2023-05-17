#include "main.h"
#define PATH_SEPARATOR " \t\r\n"

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
	char *prompt = "hsh: $ ";
	char **tokens;
	ssize_t val;
	char *buf;
	(void)argc;
	(void)argv;

	/* create an infinite loop */
	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);
		val = getline(&buf, &(size_t){0}, stdin);
		if (val == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}

		tokens = tokenize(buf);
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}

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

/**
 * execute_command - Execute a command in a new process
 * @tokens: A pointer to an array of strings (tokens)
 * representing the command and its arguments
 *
 * Description: This function receives an array of strings representing
 * a command and its arguments, checks if the command exists,
 * and executes it in a new process using the execv system call.
 * If the command does not exist, the function prints an error message and
 * returns. If there is an error in forking a new process or executing the
 * command, the function prints an error message and exits.
 * The function waits for the child process to complete before returning.
 *
 * Return: This function does not return a value.
 */
void execute_command(char **tokens)
{
#undef PATH_SEPARATOR
#define PATH_SEPARATOR "\n:"
	char *dir, *token, *path = getenv("PATH");
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *reversed_path = strdup(path);
		char *token_end = reversed_path + strlen(reversed_path) - 1;

		token = strtok_r(reversed_path, PATH_SEPARATOR, &token_end);
		while (token != NULL)
		{
			dir = malloc(strlen(token) + strlen(tokens[0]) + 2);
			if (!dir)
			{
				perror("Memory allocation error");
				free(dir);
				exit(EXIT_FAILURE);
			}
			sprintf(dir, "%s/%s", token, tokens[0]);
			if (access(dir, F_OK | X_OK) == 0)
			{
				execve(dir, tokens, environ);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			free(dir);
			token = strtok_r(NULL, PATH_SEPARATOR, &token_end);
		}
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}
