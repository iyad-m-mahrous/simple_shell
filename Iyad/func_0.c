#include "main.h"

/**
 * get_full_path - get the full path of a command
 * @command: the command
 *
 * Return: NULL if nothing else the full path
*/
char *get_full_path(char *command)
{
	char *path_env, *token, full_path[BUFF_SIZE], *temp = NULL, *saveptr;

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	temp = strdup(path_env);
	token = strtok_r(temp, ":", &saveptr);
	while (token)
	{
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (access(full_path, X_OK) == 0)
		{
			free(temp);
			return (strdup(full_path));
		}
		token = strtok_r(NULL, ":", &saveptr);
		full_path[0] = '\0';
	}
	free(temp);
	return (NULL);

}

/**
 * print_env - print the system environment variables
 * @env: Array of enviromental variables data
 *
 * Return: nothing
*/
void print_env(char *env[])
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * run_command - Reads bthe input from user and execute if valid command
 * @line: user input string
 * @line_len: length of the user input string
 * @argv: passing argv from main
 *
 * Return: Nothing
*/
void run_command(char *line, size_t line_len, char *argv[])
{
	char *args[10], *full_path = NULL, *saveptr, *error_msg = NULL;
	int i, exit_status;
	static int err_count;
	pid_t pid;

	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	if ((exit_status = check_exit(line, line_len, &error_msg)) != -1)
                {
			if (error_msg)
			{
				printf("%s: %d: %s", argv[0], ++err_count, error_msg);
				free(error_msg);
				error_msg = NULL;
				return;
			}
			free(line);
			exit(exit_status);
		}
	args[0] = strtok_r(line, " ", &saveptr);
	if (!args[0])
		return;
	full_path = get_full_path(args[0]);
	if (access(args[0], X_OK) == -1 && !full_path)
	{
		printf("%s: %d: %s: not found\n", argv[0], ++err_count, args[0]);
		return;
	}
	for (i = 1; i < 10; i++)
	{
		args[i] = strtok_r(NULL, " ", &saveptr);
		if (args[i] == NULL)
			break;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path ? full_path : args[0], args, NULL) == -1)
			perror("execve");
		if (*line)
			free(line);
		if (*full_path)
			free(full_path);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
	free(full_path);
}
