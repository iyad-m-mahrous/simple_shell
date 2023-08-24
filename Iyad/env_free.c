#include "main.h"

/**
 * env_free - free env allocated memory
 * @env: env
 *
 * Return: nothing
*/

void env_free(char *env[])
{
	int i = 0;

	while (environ[i] != NULL)
	{
		if (((unsigned long)env >> 24) != ((unsigned long)(environ[i]) >> 24))
		{
			free(environ[i]);
			environ[i] = NULL;
		}
		i++;
	}
	if (environ != env)
	{
		free(environ);
		environ = env;
	}
}
