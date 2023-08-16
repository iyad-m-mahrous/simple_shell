#include "main.h"

/**
 * check_exit - check exit input from the user
 * @line: pointer to the user input string
 * @line_len: length of the user input string
 * @error_msg: pointer to the error message passed to the main
 *
 * Return: exit code otherwise -1 if error
*/

int check_exit(char *line, ssize_t line_len, char **error_msg)
{
	char *args[10], *saveptr;
        int i, exit_status;
	char local_err[1000];

        if (line[line_len - 1] == '\n')
                line[line_len - 1] = '\0';
        args[0] = strtok_r(line, " ", &saveptr);
        if (!args[0])
                return (-1);
        for (i = 1; i < 10; i++)
        {
                args[i] = strtok_r(NULL, " ", &saveptr);
                if (args[i] == NULL)
                        break;
        }
	if (strcmp(args[0], "exit") == 0)
	{
		if (!args[1])
			return 0;
		if (strcmp(args[1], "0") == 0)
			return (0);
		if ((exit_status = _atoi(args[1])) > 0)
			return (exit_status);
		snprintf(local_err, sizeof(local_err), "exit: Illegal number: %s\n", args[1]);
		*error_msg = strdup(local_err);
		return (0);
	}
	
	*error_msg = NULL;
	return (-1);
}
