#define PATH_SEPARATOR " \t\r\n"

#include "main.h"

/* Global Variables */
int status = 0;

/**
 * noninteractive_mode - Execute shell commands in non-interactive mode
 * @program_name: Name of the shell program
 *
 * Description: This function reads shell commands from stdin in
 * non-interactive mode and executes them accordingly. It uses the getline
 * function to read input from stdin and tokenizes each line of input using the
 * tokenize function.
 * It then checks the first token to determine the appropriate action:
 *   - If the first token is 'echo $PATH', it calls the execute_echo_path
 *     function.
 *   - If the first token is 'env', it calls the execute_env function.
 *   - If the first token is 'exit', it calls the execute_exit function with
 *     the second token as the argument. If no argument is provided, the status
 *     code is set to 0 indicating successful termination.
 *   - If the first token is 'setenv', it calls the _setenv function with the
 *     corresponding arguments.
 *   - If the first token is 'unsetenv', it calls the _unsetenv function with
 *     the corresponding argument.
 *   - For any other command, it calls the execute_command function to execute
 *     a generic command.
 * The function continues reading and executing commands until the end of input
 * is reached. It frees the memory allocated for tokens and the input buffer
 * before returning.
 *
 * Return: This function does not return a value.
 */
void noninteractive_mode(char *program_name)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t val;
	char **tokens;
	int line_number = 1, status;

	while ((val = getline(&buf, &n, stdin)) != -1)
	{
		tokens = tokenize(buf);
		if (tokens == NULL)
			continue;

		if (strcmp(tokens[0], "echo") == 0 && strcmp(tokens[1], "$PATH") == 0)
			execute_echo_path();
		else if (strcmp(tokens[0], "env") == 0)
			execute_env();
		else if (strcmp(tokens[0], "exit") == 0)
		{
			status = execute_exit(tokens[1], line_number, program_name);
			free(tokens);
			free(buf);
			exit(status);
		}
		else if (strcmp(tokens[0], "setenv") == 0)
			_setenv(tokens[1], tokens[2]);
		else if (strcmp(tokens[0], "unsetenv") == 0)
			_unsetenv(tokens[1]);
		else
			execute_command(tokens, line_number, program_name);

		free(tokens);
		line_number++;
	}
	free(buf);
}

/**
 * interactive_mode - Execute shell commands in interactive mode
 * @prompt: The prompt to be displayed for user input
 * @program_name: Name of the shell program
 *
 * Description: This function runs the shell program in interactive mode,
 * where it prompts the user for input and executes the corresponding shell
 * commands. It displays the specified prompt before each user input. The
 * function uses the getline function to read input from stdin and tokenizes
 * each line of input using the tokenize function. It then checks the first
 * token to determine the appropriate action:
 *   - If the first token is 'echo $PATH', it calls the execute_echo_path
 *     function.
 *   - If the first token is 'env', it calls the execute_env function.
 *   - If the first token is 'exit', it calls the execute_exit function with
 *     the second token as the argument. The function breaks out of the loop
 *     and terminates the shell program.
 *   - If the first token is 'setenv', it calls the _setenv function with the
 *     corresponding arguments.
 *   - If the first token is 'unsetenv', it calls the _unsetenv function with
 *     the corresponding argument.
 *   - For any other command, it calls the execute_command function to execute
 *     a generic command.
 * The function continues prompting for input and executing commands until the
 * user terminates the program by entering the 'exit' command. It frees the
 * memory allocated for tokens and the input buffer before returning.
 *
 * Return: This function does not return a value.
 */
void interactive_mode(char *prompt, char *program_name)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t val;
	char **tokens;
	int line_number = 1;

	while (1)
	{
		printf("%s", prompt);
		fflush(stdout);
		val = getline(&buf, &n, stdin);
		if (val == -1)
			break;
		tokens = tokenize(buf);
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
		line_number++;
		if (strcmp(tokens[0], "echo") == 0 && strcmp(tokens[1], "$PATH") == 0)
			execute_echo_path();
		else if (strcmp(tokens[0], "env") == 0)
			execute_env();
		else if (strcmp(tokens[0], "exit") == 0)
		{
			execute_exit(tokens[1], line_number, program_name);
			free(tokens);
			break;
		}
		else if (strcmp(tokens[0], "setenv") == 0)
			_setenv(tokens[1], tokens[2]);
		else if (strcmp(tokens[0], "unsetenv") == 0)
			_unsetenv(tokens[1]);
		else
			execute_command(tokens, line_number, program_name);
		free(tokens);
	}
	free(buf);
}

/**
 * main - Entry point of the shell program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 *
 * Description: This function is the entry point of the shell program.
 * It checks if the program is running in interactive mode or non-interactive
 * mode based on whether stdin is associated with a terminal. If stdin is not a
 * terminal, the program runs in non-interactive mode by calling the
 * noninteractive_mode function with the program name. If stdin is a terminal,
 * the program runs in interactive mode by calling the interactive_mode
 * function with the specified prompt and program name.
 * The function returns 0 upon successful completion.
 *
 * Return: 0 upon successful completion.
 */
int main(int argc, char **argv)
{
	char *prompt = "hsh: $ ";
	(void)argc;

	if (!isatty(STDIN_FILENO))
	{
		noninteractive_mode(argv[0]);
	}
	else
	{
		interactive_mode(prompt, argv[0]);
	}

	return (0);
}

/**
 * tokenize - Split a string into tokens
 * @input: The string to be tokenized
 *
 * Description: This function receives a string and splits it into tokens based
 * on the delimiters " " and "\n". It uses the _strtok function to do the
 * tokenization and stores the tokens in a dynamically allocated
 * array of strings. The tokens are separated by NULL.
 * The function returns a pointer to the array of strings.
 *
 * Return: A pointer to a dynamically allocated array of strings (tokens).
 * If there is a memory allocation error, the function returns NULL.
 */
char **tokenize(char *input)
{
	char **tokens = malloc(BUFSIZE * sizeof(char *));
	char *token;
	int i;

	i = 0;
	if (!tokens)
	{
		perror("Memory allocation error");
		free(tokens);
		exit(EXIT_FAILURE);
	}

	token = strtok(input, PATH_SEPARATOR);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, PATH_SEPARATOR);
	}

	tokens[i] = NULL;
	if (i == 0)
	{
		free(tokens);
		tokens = NULL;
	}
	return (tokens);
}
