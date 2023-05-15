#include "main.h"

int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	char *buf[BUFSIZE];
	char **tokens;
	size_t n = 0;
	ssize_t val;
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

		tokens = tokenize(buf);
		if(tokens[0] == NULL)
			continue;

		if (access(tokens[0], F_OK) == -1){
			printf("%s : command not found\n", tokens[0]);
			continue;
		}

		execute_command(tokens);

		free(tokens);
	}
	return (0);
}

/**/

char **tokenize(char *input){
	char **tokens = malloc(BUFSIZE * sizeof(char*));
	char *token;
	int i;

	i = 0;
	if (!tokens){
		perror("Memory allocation error");
		return (-1);
	}

	token = strtok(input, " \n");
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}

	tokens[i] = NULL;
	return (tokens);
}
