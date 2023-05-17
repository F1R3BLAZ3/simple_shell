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
	char *path = getenv("PATH");

	printf("%s\n", path);
}

/**
 * execute_exit - Execute the 'exit' command
 *
 * Description: This function prints a goodbye message to the standard output,
 * indicating the termination of the shell program. It then exits the program
 * with a status code of 0, indicating successful termination.
 *
 * Return: This function does not return a value.
 */
void execute_exit(void)
{
	printf("Bye..\n");
	exit(0);
}

/**
 * execute_env - Execute the 'env' command
 *
 * Description: This function prints the current environment to the standard output.
 * It iterates through the `environ` variable, which is an array of strings
 * representing the environment variables in the format "key=value". Each key-value pair
 * is printed on a separate line. The function stops when it encounters a NULL value,
 * indicating the end of the environment variables.
 *
 * Return: This function does not return a value.
 */
void execute_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
