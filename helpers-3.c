#include "main.h"

/**
 * _getline - Reads input from a stream.
 * @lineptr: A pointer to a buffer to store the input.
 * @n: A pointer to the size of the buffer.
 * @stream: The stream to read from.
 *
 * Return: The number of bytes read.
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	ssize_t ret = 0;
	char *buffer = NULL;
	size_t size = 0;
	char c;
	int r;
	char *new_buffer;

	if (!lineptr || !n)
		return (0);

	while ((r = read(fileno(stream), &c, 1)) > 0 && c != '\n')
	{
		if (size == 0)
		{
			buffer = malloc(120);
			if (!buffer)
				return (0);
			size = 120;
		}
		else if ((size_t)ret >= size - 1)
		{
			new_buffer = _realloc(buffer, size, size + 120);
			if (!new_buffer)
			{
				free(buffer);
				return (0);
			}
			buffer = new_buffer;
			size += 120;
		}
		buffer[ret] = c;
		ret++;
	}

	if (ret == 0 && r <= 0)
		return (0);
	buffer[ret] = '\0';
	*lineptr = buffer;
	*n = ret;
	return (ret);
}
