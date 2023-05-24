int main(int argc, char *argvv[])
{
	char *buf, *command, **argv, **commands, *deli = " \n";
	char *delim = ",";
	int parse_return_value, i;

	if (exe_file(argc, argvv) == 0)
		return (0);
	while (1)
	{
		buf = get_user_input();
		if (strchr(buf, ';') != NULL)
			commands = strip_tokens(buf, delim);
		else
			commands = get_commands(buf);
		if (!commands)
		{
			free(buf);
			continue;
		}
		for (i = 0; commands[1] != NULL; i++)
		{
			argv = get_tokens(commands[i], deli);
			parse_return_value = parse_input(argv, commands[i], argvv[0]);
			if (parse_return_value == 0)
				continue;
			command = get_path(argv[0]);
			if (_strcmp(command, "null") != 0)
				execute(command, argv);
			else
			{
				handle_errors(argv[0], argvv[0]);
			}
			free_tokens(argv);
			free(command);
		}
		free(buf);
		free_tokens(commands);
	}
	return (0);
}
