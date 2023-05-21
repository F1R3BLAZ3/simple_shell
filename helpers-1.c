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

int _atoi(char *str, int n)
{
	if (n == 1)
		return (*str - '0');

	return (10 * _atoi(str, n - 1) + str[n - 1] - '0');
}
