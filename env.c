#include "main.h"

/**
 * _validate_setenv_input - Validates the input for the setenv function.
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 *
 * Description: This function checks if the input for the setenv function is
 * valid. It verifies that the name is not NULL, not an empty string,
 * does not contain the '=' character, and the value is not NULL.
 * If any of these conditions are not met,
 * an error message is printed and -1 is returned.
 *
 * Return: 0 if the input is valid, -1 otherwise.
 */
int _validate_setenv_input(const char *name, const char *value)
{
	if (name == NULL || name[0] == '\0' ||
	    _strchr(name, '=') != NULL || value == NULL)
	{
		perror("Invalid input for setenv\n");
		return (-1);
	}
	return (0);
}

/**
 * _setenv - Set the value of an environment variable.
 * @name: The name of the environment variable.
 * @value: The value to be assigned to the environment variable.
 *
 * Description: This function sets the value of the specified environment
 * variable. It first validates the input parameters using the
 * _validate_setenv_input function. If the input is valid, it calculates the
 * size of the new environment variable string, allocates memory for it,
 * and copies the name and value into the new_env string.
 * It then calls _replace_env_variable to check if the variable already exists
 * and replace its value, or calls _append_env_variable to add a new
 * environment variable to the environ array. Memory reallocation is performed
 * if necessary to accommodate the new environment variable.
 * If any memory allocation or reallocation fails, an error message is printed
 * and -1 is returned. Otherwise, the function returns 0, indicating success.
 *
 * Return: 0 on success, -1 on failure.
 */
int _setenv(const char *name, const char *value)
{
	size_t name_len, value_len, env_size, environ_size;
	char *new_env;
	char **new_environ;

	if (_validate_setenv_input(name, value) != 0)
		return (-1);

	name_len = _strlen(name);
	value_len = _strlen(value);
	env_size = name_len + value_len + 2;
	new_env = malloc(env_size);
	if (new_env == NULL)
	{
		perror("Failed to allocate memory for setenv\n");
		return (-1);
	}

	_strcpy(new_env, (char *)name);
	new_env[name_len] = '=';
	_strcpy(new_env + name_len + 1, (char *)value);

	if (_replace_env_variable(name, new_env) == 0)
		return (0);

	environ_size = _get_environ_size();
	new_environ = _realloc((void *)environ, environ_size * sizeof(char *),
			       (environ_size + 2) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror("Failed to reallocate memory for setenv\n");
		free(new_env);
		return (-1);
	}

	_append_env_variable(new_environ, new_env);
	return (0);
}

/**
 * _replace_env_variable - Replaces an environment variable with a new value.
 * @name: The name of the environment variable.
 * @new_env: The new environment variable string.
 *
 * Description: This function searches for an environment variable with the
 * specified name. If a match is found, the existing environment variable is
 * freed and replaced with the new value specified by `new_env`. The function
 * modifies the `environ` array directly.
 *
 * Return: 0 if the environment variable was successfully replaced,
 * -1 otherwise.
 */
int _replace_env_variable(const char *name, char *new_env)
{
	char **env;
	size_t name_len;

	env = environ;
	name_len = _strlen(name);
	while (*env != NULL)
	{
		if (_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
		{
			free(*env);
			*env = new_env;
			return (0);
		}
		env++;
	}

	return (-1);
}
/**
 * _append_env_variable - Append a new environment variable to the environ
 * array.
 * @new_environ: Pointer to the environ array.
 * @new_env: Pointer to the new environment variable string.
 *
 * Description: This function appends a new environment variable string to the
 * environ array. It calculates the size of the environ array using
 * _get_environ_size function, then assigns the new_env string to the next
 * available index in the array. Finally, it sets the next index to NULL to
 * mark the end of the array.
 *
 * Return: None.
 */
void _append_env_variable(char **new_environ, char *new_env)
{
	size_t environ_size;

	environ_size = _get_environ_size();
	new_environ[environ_size] = new_env;
	new_environ[environ_size + 1] = NULL;
}

/**
 * _get_environ_size - Get the size of the environ array.
 *
 * Description: This function calculates the size of the environ array by
 * counting the number of non-null elements until a null element is encountered
 *
 * Return: The size of the environ array.
 */
size_t _get_environ_size(void)
{
	size_t environ_size;

	environ_size = 0;
	while (environ[environ_size] != NULL)
		environ_size++;

	return (environ_size);
}
