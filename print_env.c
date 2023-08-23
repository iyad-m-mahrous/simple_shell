#include "main.h"

/**
 * Print_Env - prints the systtem environment variables
 *
 * Return: nothing
*/
void print_env(void)
{
	int i = 0;

	while (*(environ + i))
		printf("%s\n", *(environ + i++));
}
