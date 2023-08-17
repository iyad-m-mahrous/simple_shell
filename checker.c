#include "main.h"

/**
 * env_check - Convert a string to an integer.
 * @args: input tokens
 * @argv: main argv
 * @env: main env
 * @err_count: global error count ptr
 *
 * Return: 1 if Ok else -1
 */

int env_check(char *args[], char *argv[], char *env[], int *err_count)
{
	(void) argv;
	(void) err_count;

	if (strcmp(args[0], "env") == 0)
	{
		if (args[1])
			printf("env: %s: No such file or directory\n", args[1]);
		else
			print_env(env);
		return (1);
	}
	return (-1);
}

/**
 * exit_check - Convert a string to an integer.
 * @args: input tokens
 * @argv: main argv
 * @env: main env
 * @err_count: global error count ptr
 *
 * Return: exit status if Ok else -1 if not else -99 if exit with wrong args
 */
int exit_check(char *args[], char *argv[], char *env[], int *err_count)
{
	int exit_status = 0;

	(void) env;
	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1])
		{
			exit_status = _atoi(args[1]);
			if (exit_status < 0)
			{
				printf("%s: %d: exit: Illegal number: %s\n"
						, argv[0], ++(*err_count), args[1]);
				return (-99);
			}
		}
		return (exit_status);
	}
	return (-1);
}
