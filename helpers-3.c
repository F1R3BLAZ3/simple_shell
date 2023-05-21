#include "main.h"

/**
 * _getline - Reads a line from a stream and stores it in a buffer.
 * @buf: Pointer to the buffer where the line will be stored.
 * @n: Pointer to the size of the buffer.
 * @stream: Pointer to the input stream to read from.
 *
 * Description: This function reads a line from the specified input stream and
 * stores it in the buffer pointed to by buf. The buffer is dynamically resized
 * as needed to accommodate the line. The size of the buffer is stored in the n
 * variable. If the buffer is NULL or the size is 0, a new buffer of initial
 * size 128 bytes is allocated. The function uses _fgets to read the line from
 * the stream into the buffer. If the line exceeds the buffer size, the buffer
 * is extended to twice its size to accommodate the entire line. The function
 * also removes the newline character ('\n') at the end of the line if present.
 * The function returns the length of the line
 * (excluding the newline character) on success, or -1 on failure.
 *
 * Return: The length of the line read on success, or -1 on failure.
 */
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

/**
 * read_line - Reads a line from a stream and stores it in a buffer.
 * @buf: Pointer to the buffer where the line will be stored.
 * @n: Pointer to the size of the buffer.
 * @stream: Pointer to the input stream to read from.
 *
 * Description: This function reads a line from the specified input stream and
 * stores it in the buffer pointed to by buf. The size of the buffer is stored
 * in the n variable. The function uses _fgets to read the line from the stream
 * into the buffer. If the line exceeds the buffer size, it may be truncated.
 * The newline character ('\n') at the end of the line, if present, is replaced
 * with a null character ('\0'). The function returns the length of the line
 * (excluding the newline character) on success,or -1 on failure.
 *
 * Return: The length of the line read on success, or -1 on failure.
 */
ssize_t read_line(char **buf, size_t *n, FILE *stream)
{
	size_t len = _strlen(*buf);

	if (_fgets(*buf, (int)*n, stream) == NULL)
		return (-1);

	if (len > 0 && (*buf)[len - 1] == '\n')
		(*buf)[len - 1] = '\0';

	return (len);
}

/**
 * extend_buffer - Extends the size of a buffer.
 * @buf: Pointer to the buffer to be extended.
 * @n: Pointer to the size of the buffer.
 * @new_size: The new size to allocate for the buffer.
 *
 * Description: This function extends the size of the buffer pointed to by buf
 * to the specified new_size using _realloc. If the reallocation fails, the
 * function prints an error message and returns -1. If the reallocation is
 * successful, the buffer pointer and size are updated accordingly.
 * The function returns 0 on success or -1 on failure.
 *
 * Return: 0 on success, or -1 on failure.
 */
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

/**
 * read_remaining - Reads the remaining content from a stream into a buffer.
 * @buf: Pointer to the buffer.
 * @n: Pointer to the size of the buffer.
 * @stream: Pointer to the input stream.
 * @len: The current length of the buffer.
 *
 * Description: This function reads the remaining content from the specified
 * input stream into the buffer buf. It continues reading until the end of
 * file or a newline character is encountered. If the buffer is full and the
 * newline character is not encountered, the buffer is extended using the
 * extend_buffer function. The function returns the final length of the buffer
 * after reading.
 *
 * Return: The final length of the buffer after reading, or -1 on failure.
 */
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
