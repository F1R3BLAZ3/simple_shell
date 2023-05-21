#include "main.h"

/**
 * check_delim - Check if a character is a delimiter
 * @c: The character to be checked
 * @delim: A pointer to a string of delimiters
 *
 * Description: This function checks if a given character c is present in the
 * string of delimiters specified by the delim parameter. It iterates through
 * the characters in delim and compares each character to c.
 * If a match is found, the function returns 1, indicating that c is a
 * delimiter. If no match is found, the function returns 0, indicating that c
 * is not a delimiter. The function expects delim to be a null-terminated
 * string.
 *
 * Return: 1 if c is a delimiter, 0 otherwise.
 */
unsigned int check_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _strtok - Tokenize a string by a delimiter
 * @str: The string to be tokenized
 * @delim: The delimiter character
 *
 * Description: This function tokenizes a string str by a single delimiter
 * delim. It maintains a static pointer input to keep track of the current
 * position in the string. On the first call to the function, the str parameter
 * is used to initialize input. Subsequent calls to the function with str set
 * to NULL will continue tokenizing from the previous position. The function
 * skips over consecutive delimiter characters until it finds a non-delimiter
 * character. It then starts building the result string from that point until
 * it encounters another delimiter or the end of the string. The result string
 * is returned, and the static pointer input is updated to point to the next
 * position in the string after the delimiter. If the end of the string is
 * reached, NULL is returned. The function assumes that str points to a
 * null-terminated string.
 *
 * Return: A pointer to the next token in the string, or NULL if there are no more tokens.
 */
char *_strtok(char *str, char delim)
{
	static char *input = NULL;
	char *result;

	if (str)
		input = str;

	if (input == NULL)
		return (NULL);

	while (1)
	{
		if (check_delim(*str, delim))
		{
			str++;
			continue;
		}
		if (str == '\0')
		{
			return (NULL) :
		}
		break;
	}

	result = str;
	while (1)
	{
		if (*str == '\0')
		{
			input = str;
			return (result);
		}
		if (check_delim(*str, delim))
		{
			*str = '\0';
			input = str + 1;
			return (result);
		}
		str++;
	}
}
