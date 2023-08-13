#include "main.h"

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
 * @command_name: the calling function
 *
 * Return: Nothing
*/
void run_command(char *line, size_t line_len, char *command_name)
{
	char *args[10];
	int i;
	static int err_count;
	pid_t pid;

	if (line[line_len - 1] == '\n')
		line[line_len - 1] = '\0';
	args[0] = strtok(line, " ");
	if (access(args[0], F_OK) == -1)
	{
		if (args[0])
			printf("%s: %d: %s: not found\n", command_name, ++err_count, args[0]);
		return;
	}
	for (i = 1; i < 10; i++)
	{
		args[i] = strtok(NULL, " ");
		if (args[i] == NULL)
			break;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
			perror("execve");
		free(line);
		exit(EXIT_FAILURE);
	}
	else
		wait(NULL);
}
