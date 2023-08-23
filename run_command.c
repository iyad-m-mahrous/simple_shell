#include "main.h"

/**
 * run_command - Readds the inpput from userr and execute if its a valid command
 * @line: user input string
 * @line_len: length of the user input string
 * @argv: passing argv fromm main
 * @env: env
 *
 * Return: Nothing
*/
void run_command(char *line, size_t line_len, char *argv[], char *env[])
{
	char *args[BUFF_SIZE], *full_path = NULL, *saveptr = NULL;
	int i;
	static int err_count;
	pid_t pid;

	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	args[0] = _strtok_r(line, " ", &saveptr);
	if (!args[0])
		return;
	for (i = 1; i < BUFF_SIZE; i++)
	{
		args[i] = _strtok_r(NULL, " ", &saveptr);
		if (args[i] == NULL)
			break;
	}
	if (env_check(args, argv, &err_count) ||
		       exit_check(args, argv, env, &err_count, line) ||
		       _setenv(args, argv, env, &err_count, line) ||
		       _unsetenv(args, argv, env, &err_count, line))
		return;
	full_path = get_full_path(args[0]);
	if (access(args[0], X_OK) == -1 && !full_path)
	{
		printf("%s: %d: %s: not found\n", argv[0], ++err_count, args[0]);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path ? full_path : args[0], args, NULL) == -1)
			perror("execve");
		free(line);
		free(full_path);
		env_free(env);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	free(full_path);
}
