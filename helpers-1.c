#include "main.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: A pointer to the memory previously allocated.
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The size in bytes for the new memory block.
 *
 * Description: This function reallocates a memory block pointed to by ptr to a
 * new size specified by new_size. If ptr is NULL, it behaves like malloc and
 * allocates a new block of memory of size new_size. If new_size is zero and
 * ptr is not NULL, it behaves like free and frees the memory block.
 * If new_size is equal to old_size, it returns ptr without making any changes.
 * If new_size is greater than old_size, it allocates a new block of memory of
 * size new_size, copies the contents of the old block to the new block,
 * and frees the old block. If new_size is less than old_size, it allocates a
 * new block of memory of size new_size, copies the contents of the old block
 * up to new_size bytes, and frees the old block. The function ensures that the
 * minimum size used for copying is the smaller of old_size and new_size to
 * prevent out-of-bounds access. The function returns a pointer to the
 * reallocated memory block on success, or NULL if the reallocation fails or if
 * new_size is zero and ptr is NULL. The caller is responsible for managing the
 * memory block returned by this function and freeing it when no longer needed.
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
 * Description: This function copies n bytes from the memory area pointed to by
 * src to the memory area pointed to by dest. It performs a byte-by-byte copy
 * of the data. The function assumes that both src and dest are valid memory
 * areas with at least n bytes allocated. The function returns a pointer to the
 * destination memory area.
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

/**
 * _atoi - Converts a string of digits to an integer.
 * @str: The string to be converted.
 * @n: The length of the string.
 *
 * Description: This function converts a string of digits str with length n to
 * its corresponding integer value. The string can optionally start with a sign
 * ('+' or '-'). The function recursively converts each digit to its
 * corresponding numerical value and calculates the final integer by
 * multiplying each digit by the appropriate power of 10 and summing them.
 * The function assumes that the string contains only valid digits and an
 * optional sign. It does not perform any error checking or handle non-digit
 * characters. The function returns the converted integer.
 *
 * Return: The converted integer value.
 */
int _atoi(char *str, int n)
{
	if (n == 1)
		return (*str - '0');

	return (10 * _atoi(str, n - 1) + str[n - 1] - '0');
}

/**
 * _strncmp - Compare two strings up to a specified number of characters
 * @s1: The first string to compare
 * @s2: The second string to compare
 * @n: The maximum number of characters to compare
 *
 * Description: This function compares the first 'n' characters of the strings
 * 's1' and 's2'. It returns an integer value indicating the relationship
 * between the strings:
 * If the value is less than 0, it means 's1' is less than 's2'.
 * If the value is greater than 0, it means 's1' is greater than 's2'.
 * If the value is 0, it means the first 'n' characters of both strings are
 * equal.
 *
 * Return: The function returns an integer value indicating the relationship
 * between the strings.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		}
		else if (*s1 == '\0')
		{
			return (0);
		}

		s1++;
		s2++;
		n--;
	}
	return (0);
}
