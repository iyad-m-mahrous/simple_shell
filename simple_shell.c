#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>


/**
 * main - Simple Sell Task
 *
 * Return: -1 if error else 0
*/

int main(int argc, char *argv[], char *env[])
{
	char *line = NULL, *args[10];
	int i, pid = -1, is_exit = 1, is_atty, err_count = 0;
	size_t len = 0;
	ssize_t line_len;

	is_atty = isatty(0);
	(void) argc;
	while (1)
	{
		if (is_atty)
			printf("($) ");
		line_len = getline(&line, &len, stdin);
		if (line_len == -1 || (is_exit = strcmp(line,"exit\n")) == 0)
		{
			free(line);
			break;
		}
		if (strcmp(line, "env\n") == 0)
		{
			while (*env)
			{
				printf("%s\n", *env);
				env++;
			}
			free(line);
			line = NULL;
			continue;
		}
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		args[0] = strtok(line, " ");
		if (access(args[0], F_OK) == -1)
		{
			if (args[0])
				printf("%s: %d: %s: not found\n", argv[0], ++err_count, args[0]);
			free(line);
			line = NULL;
			continue;			
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
			if(execve(args[0], args, NULL) == -1)
				perror("execve");
			free(line);
			line = NULL;
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}
	if (is_exit != 0 && is_atty)
		printf("\n");
	return (0);
}
