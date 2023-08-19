#include "main.h"

/**
 * _setenv - Initialize a new environment variable,
 *         or modify an existing one.
 * @args: input tokens
 * @argv: main argv
 * @err_count: global error count ptr
 * @line: pointer to the buffer to be freed if exit
 *
 * Return: 1 if ok else 0
 */
int _setenv(char *args[], char *argv[]
		, int *err_count, char *line)
{
	int i = 0;

	(void) argv;
	(void) err_count;
	(void) line;

	if (strcmp(args[0], "setenv") == 0)
	{
		if (args[1] && args[2])
		{
			printf("HEEEERRRRE");
			i = env_var_check(args[1]);
			if (i == -1)
			{
				if (env_add(args[1], args[2]))
					return (1);
				return (0);
			}
			else
			{
				if (env_modify(i, args[1], args[2]))
					return (1);
				return (0);
			}
		}
		else
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			return (0);
		}
	}
	return (0);
}

/**
 * env_add - add new variable to env.
 * @varname: variable name
 * @varvalue: variable value
 *
 * Return: 1 if ok else 0
 */

int env_add(char *varname, char *varvalue)
{
	char **new_environ = NULL, *new_var = NULL;
	int env_size = 0, i = 0, var_size;

	while (environ[env_size] != NULL)
		env_size++;
	var_size = strlen(varname) + strlen(varvalue) + 2;
	new_var = (char *) malloc(sizeof(*new_var) * var_size);
	if (!new_var)
	{
		perror("malloc");
		return (0);
	}

	new_environ = (char **) malloc(sizeof(*new_environ) * (env_size + 2));
	if (!new_environ)
	{
		perror("malloc");
		free(new_var);
		return (0);
	}

	snprintf(new_var, var_size, "%s=%s", varname, varvalue);
	for (i = 0; i < env_size; i++)
	{
		new_environ[i] = environ[i];
	}
	new_environ[i] = new_var;
	new_environ[i + 1] = NULL;
	environ = new_environ;

	return (1);

}

/**
 * env_modify - update environ variable at index.
 * @index: location of thevariable
 * @varname: variable name
 * @varvalue: variable value
 *
 * Return: 1 if ok else 0
 */
int env_modify(int index, char *varname, char *varvalue)
{
	char *new_var = NULL;
	int var_size;

	var_size = strlen(varname) + strlen(varvalue) + 2;
	new_var = (char *) malloc(sizeof(*new_var) * var_size);
	if (!new_var)
	{
		perror("malloc");
		return (0);
	}
	snprintf(new_var, var_size, "%s=%s", varname, varvalue);
	environ[index] = new_var;
	return (1);
}

