#include "main.h"

ssize_t _getline(char **buf, size_t *n, FILE *stream)
{
	size_t len = _strlen(*buf);

	if (buf == NULL || n == NULL)
	{
		perror("Error: Invalid buffer or size");
		return (-1);
	}

	if (*buf == NULL || *n == 0)
	{
		*buf = malloc(128 * sizeof(char));
		if (*buf == NULL)
		{
			perror("Error: Memory allocation failed");
			return (-1);
		}
		*n = 128;
	}

	if (_fgets(*buf, (int)*n, stream) == NULL)
		return (-1);

	if (len > 0 && (*buf)[len - 1] == '\n')
		(*buf)[len - 1] = '\0';
	else if (len == (*n - 1) && (*buf)[len - 1] != '\n')
	{
		if (extend_buffer(buf, n, *n * 2) == -1)
			return (-1);

		if (read_remaining(buf, n, stream, len) == -1)
			return (-1);
	}

	return (len);
}


ssize_t read_line(char **buf, size_t *n, FILE *stream)
{
	size_t len = _strlen(*buf);

	if (_fgets(*buf, (int)*n, stream) == NULL)
		return (-1);

	if (len > 0 && (*buf)[len - 1] == '\n')
		(*buf)[len - 1] = '\0';

	return (len);
}


ssize_t extend_buffer(char **buf, size_t *n, size_t new_size)
{
	char *new_buf = _realloc(*buf, *n, new_size);

	if (new_buf == NULL)
	{
		perror("Error: Memory reallocation failed");
		return (-1);
	}

	*buf = new_buf;
	*n = new_size;

	return (0);
}


ssize_t read_remaining(char **buf, size_t *n, FILE *stream, size_t len)
{
	while (_fgets(*buf + len, (int)(*n - len), stream) != NULL)
	{
		len += _strlen(*buf + len);
		if (len > 0 && (*buf)[len - 1] == '\n')
		{
			(*buf)[len - 1] = '\0';
			break;
		}

		if (len == (*n - 1) && (*buf)[len - 1] != '\n')
		{
			if (extend_buffer(buf, n, *n * 2) == -1)
				return (-1);
		}
	}

	return (len);
}
