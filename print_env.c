#include "main.h"

/**
 * print_env - print the system environment variables
 *
 * Return: nothing
*/
void print_env(void)
{
	int i = 0;

	while (*(environ + i))
		printf("%s\n", *(environ + i++));
}
