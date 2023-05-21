#include "main.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Return: If new_size == old_size - ptr.
 *         If new_size == 0 and ptr is not NULL - NULL.
 *         Otherwise - a pointer to the reallocated memory block.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;
	size_t min_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}

	if (new_size == old_size)
	{
		return (ptr);
	}

	if (old_size < new_size)
	{
		min_size = old_size;
	}
	else
	{
		min_size = new_size;
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}

	_memcpy(new_ptr, ptr, min_size);
	free(ptr);

	return (new_ptr);
}

/**
 * _memcpy - Copies n bytes from memory area src to memory area dest.
 * @dest: The memory area to be copied to.
 * @src: The memory area to be copied from.
 * @n: The number of bytes to be copied.
 *
 * Return: A pointer to dest.
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

ssize_t _getline(char **buf, size_t *n, FILE *stream)
{
    size_t new_size;
    size_t len;
    char *new_buf;

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

    if (fgets(*buf, (int)*n, stream) == NULL)
        return (0);

    len = _strlen(*buf);

    if (len > 0 && (*buf)[len - 1] == '\n')
        (*buf)[len - 1] = '\0';
    else if (len == (*n - 1) && (*buf)[len - 1] != '\n')
    {
        new_size = *n * 2;
        new_buf = _realloc(*buf, *n, new_size);
        if (new_buf == NULL)
        {
            perror("Error: Memory reallocation failed");
            return (-1);
        }
        *buf = new_buf;
        *n = new_size;

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
                new_size = *n * 2;
                new_buf = _realloc(*buf, *n, new_size);
                if (new_buf == NULL)
                {
                    perror("Error: Memory reallocation failed");
                    return (-1);
                }
                *buf = new_buf;
                *n = new_size;
            }
        }
    }
    return (len);
}
