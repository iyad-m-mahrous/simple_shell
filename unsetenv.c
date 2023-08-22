#include "main.h"

/**
 * _unsetenv - Remove an environment variable.
 * @args: input tokens
 * @argv: main argv
 * @env: env
 * @err_count: global error count ptr
 * @line: pointer to the buffer to be freed if exit
 *
 * Return: 1 if ok else 0
 */
int _unsetenv(char *args[], char *argv[], char *env[]
		, int *err_count, char *line)
{
	int i = 0;

	(void) argv;
	(void) err_count;
	(void) line;

	if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1])
		{
			i = env_var_check(args[1]);
			if (i == -1)
			{
				fprintf(stderr, "unsetenv: Variable not found\n");
				return (1);
			}
			else
			{
				if (!env_del(i, env))
					fprintf(stderr, "unsetenv: Failed to delete VARIABLE\n");
				return (1);
			}
		}
		else
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return (1);
		}
	}
	return (0);
}

/**
 * env_del - remove variable at index.
 * @index: location of the variable
 * @env: env
 *
 * Return: 1 if ok else 0
 */

int env_del(int index, char *env[])
{
	char **new_environ = NULL;
	int i = 0, j = 0, env_size = 0;

	while (environ[env_size] != NULL)
		env_size++;
	new_environ = (char **) malloc(sizeof(*new_environ) * (env_size));
	if (!new_environ)
	{
		perror("malloc");
		return (0);
	}

	for (i = 0, j = 0; i < (env_size); i++, j++)
	{
		if (j == index)
			j++;
		new_environ[i] = environ[j];
	}
	if (((unsigned long)env >> 24) != ((unsigned long)environ[index] >> 24))
		free(environ[index]);
	if (env != environ)
		free(environ);
	environ = new_environ;

	return (1);
}
