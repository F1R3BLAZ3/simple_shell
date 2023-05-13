#include "main.h"

int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	char *buf;
	*buf_copy;
	size_t n = 0;
	ssize_t val;
	(void)argc;
	(void)argv;
	const char *delim = " \n"

	    /* create an infinite loop */
	    while (1)
	{
		printf("%s", prompt);
		val = getline(&buf, &n, stdin);
		if (val == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}

		printf("%s\n", buf);

		buf_copy = malloc(sizeof(char) * val);
		if (buf_copy == NULL)
		{
			perror("hsh: memory allocation error");
			return (-1);
		}

		free(buf);
	}

	return (0);
}
