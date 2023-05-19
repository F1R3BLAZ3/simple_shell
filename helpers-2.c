#define MAX_LINE_LENGTH 256

#include "main.h"

/**
 * read_data - Read data from the file stream into a buffer
 * @buffer: The buffer where the data is stored
 * @remaining: The number of bytes remaining to be read
 * @stream: The file stream to read from
 *
 * Description: This function reads data from the specified file stream
 * into the buffer. It reads at most `remaining` bytes from the stream using
 * the `read` system call. It returns the number of bytes read, or -1 if an
 * error occurs.
 *
 * Return: On success, the number of bytes read from the stream is returned.
 * If an error occurs, -1 is returned.
 */
int read_data(char *buffer, int remaining, FILE *stream)
{
	int n = read(fileno(stream), buffer, remaining);

	return (n);
}

/**
 * process_buffer - Process the buffer and extract a line of text
 * @str: The buffer where the line is stored
 * @buffer: The temporary buffer containing the read data
 * @bytesRead: The number of bytes read from the stream
 *
 * Description: This function processes the buffer and extracts a line of text
 * into the `str` buffer. It copies the characters from the `buffer` to the
 * `str` buffer until a newline character is encountered or the end of the
 * buffer is reached. If a newline character is encountered, it is stored in
 * `str`, the temporary `buffer` is freed, and `str` is returned. If the end of
 * the buffer is reached before reading any newline character, the function
 * returns NULL. The `bytesRead` parameter indicates the number of bytes read
 * from the stream. The `size` parameter is the maximum number of characters to
 * be read (including the null terminator).
 *
 * Return: On success, the `str` buffer containing the read line of text
 * (including the newline character) is returned. If the end of the buffer is
 * reached before reading any newline character, NULL is returned.
 */
char *process_buffer(char *str, char *buffer, int bytesRead)
{
	int i;
	int totalBytesRead = 0;

	for (i = 0; i < bytesRead; i++)
	{
		if (buffer[i] == '\n')
		{
			str[totalBytesRead] = '\n';
			totalBytesRead++;
			buffer[i] = '\0';
			free(buffer);
			return (str);
		}
		str[totalBytesRead] = buffer[i];
		totalBytesRead++;
	}

	free(buffer);
	if (totalBytesRead == 0)
		return (NULL);

	str[totalBytesRead] = '\0';
	return (str);
}

/**
 * _fgets - Read a line from a file stream into a string
 * @str: The buffer where the line is stored
 * @size: The maximum number of characters to be read
 * (including the null terminator)
 * @stream: The file stream to read from
 *
 * Description: This function reads a line of text from the specified file
 * stream stream into the buffer str. The reading stops when either size-1
 * characters are read, a newline character is encountered,
 * or the end-of-file (EOF) is reached. The newline character is stored in the
 * buffer as well. The function reads data from the file stream using the read
 * system call and reads the data in chunks into a temporary buffer.
 * It then copies the characters from the temporary buffer to the output buffer
 * str. If a newline character is encountered, it is stored in str, the
 * temporary buffer is freed, and str is returned. If the end-of-file (EOF) is
 * reached before reading any characters, the function returns NULL. Otherwise,
 * it adds the null terminator to str and returns it. The function handles
 * memory allocation errors by freeing the temporary buffer and returning NULL.
 * Note that the MAX_LINE_LENGTH macro is used as the buffer size for the
 * temporary buffer.
 *
 * Return: On success, the function returns str, which contains the read line
 * of text (including the newline character).
 * If the end-of-file is reached before reading any characters, the function
 * returns NULL. If there is a memory allocation error, the function also
 * returns NULL.
 */
char *_fgets(char *str, int size, FILE *stream)
{
	int totalBytesRead, remaining, bytesRead;
	char *buffer;

	totalBytesRead = 0, bytesRead = 0;

	if (str == NULL || size <= 0 || stream == NULL)
		return (NULL);

	buffer = (char *)malloc(MAX_LINE_LENGTH * sizeof(char));

	if (buffer == NULL)
		return (NULL);

	while (totalBytesRead < size - 1)
	{
		remaining = size - totalBytesRead - 1;

		bytesRead = read_data(buffer, remaining, stream);

		if (bytesRead <= 0)
			break;

		str = process_buffer(str, buffer, bytesRead);
		if (str != NULL)
			return (str);

		totalBytesRead += bytesRead;
	}

	free(buffer);
	if (totalBytesRead == 0)
		return (NULL);

	str[totalBytesRead] = '\0';
	return (str);
}
