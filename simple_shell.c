#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define DELIM " \t\r\n\a"

char *program_name;

void execute_command(char *command);
char **split_command(char *command);
int count_tokens(char *command);

int main(int argc, char *argv[])
{
	char *command;
	size_t buffer_size = BUFFER_SIZE;

	if (argc > 0)
		program_name = argv[0];
	else
		program_name = "hsh";

	while (1)
	{
		printf("$ ");

		command = (char *)malloc(buffer_size * sizeof(char));
		if (command == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		if (getline(&command, &buffer_size, stdin) == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}

		command[strcspn(command, "\n")] = '\0';

		execute_command(command);

		free(command);
	}

	return EXIT_SUCCESS;
}

void execute_command(char *command)
{
	pid_t pid;
	int status;
	char **args;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		args = split_command(command);

		if (execvp(args[0], args) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", program_name, args[0]);
			exit(EXIT_FAILURE);
		}

		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

char **split_command(char *command)
{
	char *token;
	int i = 0;

	int token_count = count_tokens(command);
	char **tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, DELIM);
	}
	tokens[i] = NULL;

	return tokens;
}

int count_tokens(char *command)
{
	int count = 0;
	int in_token = 0;

	while (*command != '\0')
	{
		if (*command == ' ' || *command == '\t' || *command == '\r' || *command == '\n' || *command == '\a')
		{
			in_token = 0;
		}
		else if (in_token == 0)
		{
			in_token = 1;
			count++;
		}

		command++;
	}

	return count;
}
