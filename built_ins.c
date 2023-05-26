#include "main.h"

/**
 * execute_echo_path - Execute the 'echo $PATH' command
 *
 * Description: This function retrieves the value of the environment variable
 * 'PATH' using the `getenv` function. It then prints the value of 'PATH'
 * to the standard output, followed by a newline character. The function is
 * designed to mimic the behavior of the 'echo $PATH' command in a shell.
 *
 * Return: This function does not return a value.
 */
void execute_echo_path(void)
{
	char *path = _getenv("PATH");

	_write(path);
	_write("\n");
}

/**
 * execute_exit - Execute the 'exit' command
 * @argument: The argument provided to the 'exit' command
 *
 * Description: This function prints a goodbye message to the standard output,
 * indicating the termination of the shell program. It then exits the program
 * with a status code of 0, indicating successful termination.
 *
 * Return: This function does not return a value.
 */
int execute_exit(char *argument)
{
	int status = 0;

	if (argument != NULL)
	{
		status = atoi(argument);
	}
	return (status);
}
