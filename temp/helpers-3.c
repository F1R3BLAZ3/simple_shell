#include "main.h"

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
