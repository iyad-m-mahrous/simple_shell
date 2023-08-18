#include "main.h"

/**
 * print_env - print the system environment variables
 * @env: Array of enviromental variables data
 *
 * Return: nothing
*/
void print_env(char *env[])
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
