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
	char *path = search_path(tokens);
	int status;

	if (path == NULL)
	{
		_write("Command not found\n");
		return;
	}

	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(path, tokens, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
	}
}

/**
 * search_path - Search for a command in the directories specified by
 * the PATH environment variable
 * @tokens: A pointer to an array of strings (tokens) representing the command
 * and its arguments
 *
 * Description: This function searches for a command in the directories
 * specified by the PATH environment variable.
 * It takes an array of strings representing the command and its arguments.
 * If the first token in the array contains a forward slash ('/'),
 * indicating a full path, the function returns a duplicate of the token.
 * Otherwise, the function searches for the command in each directory
 * specified by the PATH variable. It iterates through the directories,
 * constructs a path by concatenating the directory and the command,
 * and checks if the constructed path is a valid executable using the access
 * function with the F_OK and X_OK flags. If a valid executable is found,
 * the function returns a dynamically allocated string containing the full path
 * to the command. If no valid executable is found, the function returns NULL.
 * The function also handles memory allocation errors
 * by printing an error message and exiting.
 *
 * Return: A dynamically allocated string containing the full path
 * to the command if it is found in one of the directories specified by
 * the PATH variable. If the command is not found or there is a memory
 * allocation error, the function returns NULL.
 */
char *search_path(char **tokens)
{
	char *dir, *token, *path = getenv("PATH");
	char *path_copy = _strdup(path);

	if (_strchr(tokens[0], '/'))
	{
		return (_strdup(tokens[0]));
	}

	token = strtok(path_copy, PATH_SEPARATOR);
	while (token != NULL)
	{
		dir = malloc(_strlen(token) + _strlen(tokens[0]) + 2);
		if (!dir)
		{
			perror("Memory allocation error");
			free(dir);
			exit(EXIT_FAILURE);
		}
		sprintf(dir, "%s/%s", token, tokens[0]);
		if (access(dir, F_OK | X_OK) == 0)
		{
			free(path_copy);
			return (dir);
		}
		free(dir);
		token = strtok(NULL, PATH_SEPARATOR);
	}
	free(path_copy);
	return (NULL);
}
