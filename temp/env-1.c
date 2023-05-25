#include "main.h"
#include "leak_detector_c.h"

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
 * Return: A pointer to the value of the environment variable,
 * or NULL if not found.
 */
char *_getenv(const char *name)
{
	int i;
	size_t l;
	const char *value;

	l = _strlen(name);

	if (!environ || !*name || _strchr(name, '='))
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(name, environ[i], l) == 0 && environ[i][l] == '=')
		{
			value = environ[i] + l + 1;
			return ((char *)value);
		}
	}

	return (NULL);
}

/**
 * _shift_env_pointers - Shifts the environment variable pointers to fill the
 * gap.
 * @env: The environment variable array.
 * @index: The starting index to shift from.
 *
 * Description: This function shifts the environment variable pointers starting
 * from the specified index. It moves each pointer one position to the left,
 * effectively filling the gap created by removing an environment variable.
 * The end of the array is marked by a NULL pointer.
 *
 * Return: None.
 */
void _shift_env_pointers(char **env, size_t index)
{
	while (env[index] != NULL)
	{
		env[index] = env[index + 1];
		index++;
	}
}

/**
 * _unsetenv - Unset an environment variable.
 * @name: The name of the environment variable to unset.
 *
 * Description: This function unsets the environment variable specified by the
 * given name. It searches for the variable in the environment variable array
 * and removes it if found. The function performs a case-sensitive search.
 * If the variable is successfully unset, the environment variable array is
 * shifted to fill the gap. If the variable is not found, an error message
 * is printed.
 *
 * Return: On success, 0 is returned. On failure, -1 is returned.
 */
int _unsetenv(const char *name)
{
	size_t name_len;
	char **env;
	int found;

	if (name == NULL || name[0] == '\0' || _strchr(name, '=') != NULL)
	{
		perror("Invalid input for unsetenv\n");
		return (-1);
	}

	name_len = strlen(name);
	env = environ;
	found = 0;

	while (*env != NULL)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			free(*env);
			_shift_env_pointers(env, 0);
			found = 1;
		}
		else
		{
			env++;
		}
	}

	if (!found)
	{
		perror("Environment variable not found\n");
		return (-1);
	}

	return (0);
}
