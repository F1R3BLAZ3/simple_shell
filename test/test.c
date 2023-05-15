#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	char *command;
	int status;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		command = getline(NULL, 0, stdin);
		if (command == NULL)
		{
			break;
		}

		pid_t pid = fork();
		if (pid == 0)
		{
			execve(command, NULL, environ);
			perror("execve");
			exit(1);
		}

		wait(&status);
	}

	return 0;
}
