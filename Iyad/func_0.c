#include "main.h"

/**
 * get_full_path - get the full path of a command
 * @command: the command
 *
 * Return: NULL if nothing else the full path
*/
char *get_full_path(char *command)
{
	char *path_env, *token, full_path[250], *temp = NULL, *saveptr;

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
			return (strdup(full_path));
		token = strtok_r(NULL, ":", &saveptr);
		full_path[0] = '\0';
	}
	return (NULL);

}

/**
 * _getline - similar to getline function
 * @line: buffer containing the retrieved characters
 * @len: length of the buffer
 * @stream: File stream
 *
 * Return: -1 if error else the number of characters retrieved
*/
ssize_t _getline(char **line, size_t *len, FILE *stream)
{
	ssize_t line_len;

	line_len = getline(line, len, stream);
	return (line_len);
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
	char *args[10], *full_path = NULL, *saveptr;
	int i;
	static int err_count;
	pid_t pid;

	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
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
		free(line);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
