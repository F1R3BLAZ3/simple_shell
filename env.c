#include "main.h"

/**
 * _getenv - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Description: This function retrieves the value of the environment variable
 * specified by name. It searches through the environment variable array
 * environ to find a match. The function compares the first l characters of
 * each environment variable name with name using _strncmp function,
 * where l is the length of name. If a match is found, a pointer to the
 * corresponding environment variable is returned. If no match is found,
 * NULL is returned.
 *
 * Return: A pointer to the value of the environment variable, or NULL if not found.
 */
char **_getenv(const char *name)
{
	
        extern char **environ;
        int i;
	size_t l;

	l = _strlen(name);

	if (!environ || !*name || _strchr(name, '='))
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(name, environ[i], l) == 0)
			return (&environ[i]);
	}

	return (NULL);
}
