#include "main.h"

/**
 * main - Simple Shell Task
 * @argc: No. of arguments
 * @argv: passed arguments
 * @env: array of environment data
 *
 * Return: -1 if error else 0
*/

int main(int argc, char *argv[], char *env[])
{
	char *line = NULL;
	int is_atty;
	size_t len = 0;
	ssize_t line_len = 0;

	is_atty = isatty(0);
	(void) argc;
	while (1)
	{
		if (is_atty)
			printf("($) ");
		line_len = _getline(&line, &len, stdin);
		if (line_len == -1)
			break;
		if (!strcmp(line, "exit\n"))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(line, "env\n") == 0)
		{
			print_env(env);
			continue;
		}
		run_command(line, line_len, argv);
	}
	free(line);
	if (is_atty)
		printf("\n");
	return (0);
}
