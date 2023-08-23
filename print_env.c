#include "main.h"

/**
 * print_env - prinst the systtem environment variiables
 *
 * Return: nothing
*/
void print_env(void)
{
	int i = 0;

	while (*(environ + i))
		printf("%s\n", *(environ + i++));
}
