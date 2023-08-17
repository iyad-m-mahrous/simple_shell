#include "main.h"

/**
 * _atoi - Convert a string to an integer.
 * @s: The pointer to convert
 *
 * Return: An integer
 */
int _atoi(char *s)
{
	int num = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (i == 0 && s[i] == '+')
			continue;
		if (s[i] >= '0' && s[i] <= '9')
		{
			num = (num * 10) + (s[i] - '0');
		}
		else
		{
			num = -1;
			break;
		}
	}

	return (num);
}
