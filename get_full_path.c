#include "main.h"

/**
 * Get_full_path - gets the full pathh of a command
 * @command: the command
 *
 * Return: NULL if nothing else the full path
*/
char *get_full_path(char *command)
{
	char *path_env, *token, full_path[BUFF_SIZE], *temp = NULL, *saveptr = NULL;

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		perror("getenv");
		exit(EXIT_FAILURE);
	}
	temp = strdup(path_env);
	token = _strtok_r(temp, ":", &saveptr);
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
		token = _strtok_r(NULL, ":", &saveptr);
		full_path[0] = '\0';
	}
	free(temp);
	return (NULL);

}
