#include "main.h"
#define PATH_SEPARATOR " \n"

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

	token = strtok(input, " \n");
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
	pid_t pid;
	char *actual_command;

	if (access(tokens[0], X_OK) == -1)
	{
		printf("%s : command not found\n", tokens[0]);
		return;
	}

	actual_command = get_location(tokens[0]);
	pid = fork();
	if (pid == -1)  
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(actual_command, tokens, environ) == -1)
		{
			perror("Error");
		}
		else
		{
			execve(actual_command, tokens, environ);
		}
	}
	else
	{
		wait(NULL);
	}
}

char *get_location(char *command)
{
	#undef PATH_SEPARATOR
	#define PATH_SEPARATOR ":"
	char *path, *path_copy, *path_token, *file_path;
	int cmd_len, dir_len;
	struct stat buf;

	path = getenv("PATH");
	if (path == NULL)
		return (NULL);

	if (path)
	{
		path_copy = strdup(path);
		if (path_copy == NULL)
			return (NULL);

		cmd_len = strlen(command);

		path_token = strtok(path_copy, PATH_SEPARATOR);

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);

			file_path = malloc(cmd_len + dir_len + 2);
			if (file_path == NULL)
			{
				free(path_copy);
				return (NULL);
			}

			snprintf(file_path, cmd_len + dir_len + 2, "%s/%s", path_token, command);

			if (stat(file_path, &buf) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, PATH_SEPARATOR);
			}
		}
		free(path_copy);

		if (stat(command, &buf) == 0)
		{
			return (command);
		}
		return (NULL);
	}
	return(NULL);
}
