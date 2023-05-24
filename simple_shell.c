#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define DELIM " \t\r\n\a"

char *program_name;

int execute_command(char **args);
char **split_command(char *command);
int count_tokens(char *command);
char *get_command_path(char *command);

int main(int argc, char *argv[])
{
	char *command;
	size_t buffer_size = BUFFER_SIZE;
	int interactive_mode = isatty(STDIN_FILENO);
	int command_executed = 0;

	if (argc > 0)
		program_name = argv[0];
	else
		program_name = "hsh";

	while (1)
	{
		if (interactive_mode || !command_executed)
		{
			printf("$ ");
			fflush(stdout);
		}

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

		command_executed = 1;
	}

	return EXIT_SUCCESS;
}

int execute_command(char **args)
{
    pid_t pid;
    int status;
    char *command_path;

    pid = fork();
    if (pid == 0)
    {
        command_path = get_command_path(args[0]);
        if (command_path == NULL)
        {
            perror("command not found");
            exit(EXIT_FAILURE);
        }
        execvpe(command_path, args, environ);
        perror("execvpe");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    return 1;
}


char **split_command(char *command)
{
	const char *delimiters = " \t\r\n\v\f";
	char **tokens = NULL;
	char *token;
	int position = 0;
	int buffer_size = TOKEN_BUFFER_SIZE;

	tokens = malloc(buffer_size * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(command, delimiters);
	while (token != NULL)
	{
		tokens[position] = strdup(token);
		position++;

		if (position >= buffer_size)
		{
			buffer_size += TOKEN_BUFFER_SIZE;
			tokens = realloc(tokens, buffer_size * sizeof(char *));
			if (tokens == NULL)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, delimiters);
	}

	tokens[position] = NULL;

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

char *get_command_path(char *command)
{
    char *path_env = getenv("PATH");
    char *dir;
    char *path;
    char *full_path;

    path = strtok(path_env, ":");
    while (path != NULL)
    {
        full_path = malloc(strlen(path) + strlen(command) + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        sprintf(full_path, "%s/%s", path, command);
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
        path = strtok(NULL, ":");
    }

    return NULL;
}
