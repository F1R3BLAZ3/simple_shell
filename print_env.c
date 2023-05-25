#include "main.h"

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
