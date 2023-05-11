#include "main.h"

int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	char *buf;
	size_t n = 0;
	(void)argc;
	(void)argv;

	printf("%s", prompt);
	getline(&buf, &n, stdin);
	printf("%s\n", buf);

	free(buf);
	return (0);
}
