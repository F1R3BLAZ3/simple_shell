#include "main.h"

/**
 * _write - Write a string to standard output
 * @str: The string to write
 *
 * Description: This function writes the given string to the standard output.
 * It uses the `write` system call to perform the write operation.
 *
 * Return: The number of characters written, or -1 on error.
 */
ssize_t _write(const char *str)
{
	ssize_t len = 0;
	ssize_t ret;

	if (str == NULL)
		return (-1);

	while (str[len] != '\0')
		len++;

	ret = write(STDOUT_FILENO, str, len);
	if (ret == -1)
		return (-1);

	return (ret);
}

/**
 * _strcmp - Compares two strings.
 * @s1: First string.
 * @s2: Second string.
 *
 * Description: This function compares two strings, `s1` and `s2`, and
 * determines their relative ordering based on their ASCII values. The
 * comparison is performed character by character until a difference is
 * found or one of the strings reaches its null terminator. If the two
 * strings are identical, the function returns 0. If `s1` is found to be
 * less than `s2`, a value less than 0 is returned. If `s1` is found to be
 * greater than `s2`, a value greater than 0 is returned.
 *
 * Return: The difference in ASCII value between the two strings.
 * A value less than 0 if s1 is found to be less than s2, a value greater
 * than 0 if s1 is found to be greater than s2, and 0 if the two strings are
 * identical.
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i]; i++)
	{
		if (s1[i] == '\0')
		{
			return (0);
		}
	}

	return (s1[i] - s2[i]);
}

/**
 *  _strchr - Locates a character in a string.
 * @s: Pointer to string in which the character is to be searched.
 * @c: The character to be located.
 *
 * Description: This function searches for the first occurrence of the
 * character 'c' in the string 's'. It iterates through the string and checks
 * each character against 'c'. If a match is found, a pointer to the first
 * occurrence of 'c' in 's' is returned. If 'c' is the null character ('\0'),
 * the function returns a pointer to the null terminator of 's'. If 'c' is not
 * found in 's', the function returns NULL.
 *
 * Return: A pointer to the first occurrence of the character c
 * in the string s, or NULL if the character is not found.
 */
char *_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (s);
		}
		s++;
	}
	if (c == '\0')
	{
		return (s);
	}
	return (0);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory,
 * which contains a copy of the string given as a parameter
 * @str: string to be duplicated
 *
 * Description: This function takes a string 'str' and creates a new string
 * that is an exact copy of 'str'. It allocates memory for the duplicated
 * string and copies the characters from 'str' into the new memory block.
 * The duplicated string is terminated with a null character ('\0').
 * If 'str' is NULL or if there is insufficient memory to allocate for the
 * duplicate, the function returns NULL.
 *
 * Return: pointer to the duplicated string, or NULL if insufficient memory
 * was available or str was NULL
 */
char *_strdup(char *str)
{
	char *dup;
	unsigned int len, i;

	if (str == NULL)
	{
		return (NULL);
	}

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}

	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len; i++)
	{
		dup[i] = str[i];
	}

	dup[len] = '\0';

	return (dup);
}

/**
 * _strlen - Returns the length of a string.
 * @s: The string to be measured.
 *
 * Description: This function calculates the length of a string 's'
 * recursively. It checks if the current character is the null terminator
 * ('\0'). If it is, it returns 0, indicating the end of the string.
 * Otherwise, it adds 1 to the length and calls itself with the next character
 * in the string until the null terminator is reached.
 *
 * Return: The length of the string.
 */
int _strlen(char *s)
{
	if (*s == '\0')
	{
		return (0);
	}
	return (1 + _strlen(s + 1));
}
