#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


/**
 * main - Simple Sell Task
 *
 * Return: -1 if error else 0
*/

int main(void)
{
	char *line = NULL, *args[10];
	int i, pid, is_exit = 1, is_atty;
	size_t len = 0;
	ssize_t line_len;
	
	is_atty = isatty(0);
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
		if (line[line_len - 1] == '\n')
			line[line_len - 1] = '\0';
		args[0] = strtok(line, " ");
		for (i = 1; i < 10; i++)
		{
			args[i] = strtok(NULL, " ");
			if (args[i] == NULL)
				break;
		}
		if (is_atty)
			pid = fork();
		if (pid == 0 || !is_atty)
		{
			execve(args[0], args, NULL);
			free(line);
			line = NULL;
			return (0);
		}
		else
			wait(NULL);
	}
	if (is_exit != 0)
		printf("\n");
	return (0);
}
