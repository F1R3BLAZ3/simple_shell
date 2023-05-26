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
 * @line_number: The line number where the 'exit' command was encountered
 * @program_name: The name of the program
 *
 * Description: This function prints a goodbye message to the standard output,
 * indicating the termination of the shell program. It then exits the program
 * with a status code based on the provided argument. If no argument is
 * provided, the status code is 0, indicating successful termination. If the
 * argument is a valid integer, it is converted to an integer and used as the
 * status code. If the argument is not a valid integer, an error message is
 * printed to the standard error, and the status code is set to 2. The function
 * returns the status code.
 *
 * Return: The status code for the program.
 */
int execute_exit(char *argument, int line_number, char *program_name)
{
	int status = 0;

	if (argument == NULL)
	{
		/* No argument provided */
		return (status);
	}
	if (isdigit(argument[0]))
	{
		/* Argument is an integer */
		status = atoi(argument);
	}
	else
	{
		/* Argument is a string */
		fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
			 program_name, line_number, argument);
		status = 2;
	}
	return (status);
}
