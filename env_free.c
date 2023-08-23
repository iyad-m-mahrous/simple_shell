#include "main.h"

/**
 * env_free - frees env alloccated memory
 * @env: env
 *
 * Return: nothing
*/

void env_free(char *env[])
{
	int i = 0;

	if (environ != env)
	{
		while (environ[i] != NULL)
		{
			if (((unsigned long)environ >> 24) == ((unsigned long)(environ[i]) >> 24))
			{
				free(environ[i]);
				environ[i] = NULL;
			}
			i++;
		}
		free(environ);
		environ = env;
	}
}
