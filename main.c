#include "main.h"

int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	char *buf;
	size_t n = 0;
	(void)argc;
	(void)argv;

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

		free(buf);
	}

	return (0);
}
