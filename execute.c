#undef PATH_SEPARATOR
#define PATH_SEPARATOR "\n:"

#include "main.h"

/**
 * execute_command - Execute a command
 * @tokens: Array of strings representing the command and its arguments
 * @program_name: Name of the program
 *
 * Description: This function executes a command by forking a child process,
 * using the execve system call to execute the command, and waiting for the
 * child process to finish. The function checks if the command exists in the
 * PATH directories, and if not, it prints an error message using the
 * print_error function. If the command exists, the function uses execve to
 * execute the command with the given arguments. The function also handles
 * errors that may occur during forking and executing the command.
 */
void execute_command(char **tokens, int line_number, char *program_name)
{
	pid_t child_pid;
	char *path = search_path(tokens);
	int status;

	if (path == NULL)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", program_name, line_number, tokens[0]);
		exit(127);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork error");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
		{
			perror("Execve error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
	free(path);
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
	char *dir, *token, *path = _getenv("PATH");
	char *path_copy = _strdup(path);

	if (_strchr(tokens[0], '/'))
	{
		free(path_copy);
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
		token = strtok(NULL, PATH_SEPARATOR);
		free(dir);
	}
	free(path_copy);
	return (NULL);
}
