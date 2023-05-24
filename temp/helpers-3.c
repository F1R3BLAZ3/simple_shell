#include "main.h"


/**
 * _getline - Read a line of input from a file stream
 * @lineptr: Pointer to a buffer that will hold the read line
 * @n: Pointer to the size of the allocated buffer
 * @stream: The file stream to read from
 * Description: This function reads a line of input from the specified file
 * stream and stores it in the buffer pointed to by lineptr. The buffer is
 * dynamically resized as needed to accommodate the input. The size of the
 * allocated buffer is tracked by the n parameter.
 * he function reads data in
 * chunks from the stream using a static buffer to minimize the number of
 * read system calls
 * It continues reading until it encounters a newline
 * character ('\n') or reaches the end of the stream.
 * The final line, including the newline character, is stored in lineptr.
 * The function returns the number of characters read, excluding
 * the newline character, or -1 if an error occurs
 * or the end of the stream is reached before any characters are read.
 * Return: The number of characters read, excluding the newline character,
 * or -1 on failure or end of stream.
*/

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char buffer[BUFSIZE];
	static size_t position, bytesRead;

	char *line = NULL;
	size_t lineSize = 0;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	while (1)
	{
		if (position >= bytesRead)
		{
			position = 0;
			bytesRead = read(fileno(stream), buffer, BUFSIZE);

			if (bytesRead <= 0)
				break;
		}

		while (position < bytesRead)
		{
			if (lineSize % BUFSIZE == 0)
				line = _realloc(line, lineSize, lineSize + BUFSIZE);
			if (buffer[position] == '\n')
			{
				line[lineSize] = '\0';
				position++;
				*lineptr = line;
				*n = lineSize;
				return (lineSize);
			}
			else
			{
				line[lineSize] = buffer[position];
				lineSize++;
				position++;
			}
		}
	}
	free(line);
	return (-1);
}
