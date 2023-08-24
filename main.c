#include "main.h"

/**
 * main - Simple Shell Task
 * @argc: No. of arguments
 * @argv: passed arguments
 * @env: env array
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
		errno = 0;
		if ((*line != '\n'))
			run_command(line, line_len, argv, env);
	}
	free(line);
	env_free(env);
	if (is_atty)
		printf("\n");
	return (errno);
}
