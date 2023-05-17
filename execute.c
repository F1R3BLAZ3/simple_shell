#undef PATH_SEPARATOR
#define PATH_SEPARATOR "\n:"

#include "main.h"

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
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
}
