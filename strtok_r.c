#include "main.h"

/**
 * _Strtok_r - Gets the striing token from lon string
 * @str: pointer to the string
 * @delim: separator delimeter
 * @saveptr: pointer to next token
 *
 * Return: pointer to the token or NULL if nothing
*/

char *_strtok_r(char *str, const char *delim, char **saveptr)
{
	int i = 0;
	static char *tok_ptr;


	if (!str && !(*saveptr))
		return (NULL);
	if (str && str[0] && !(*saveptr))
		*saveptr = str;
	for (i = 0; (*saveptr)[i] == (*delim); i++)
		;
	tok_ptr = (*saveptr) + i;
	if ((*tok_ptr) == '\0')
	{
		tok_ptr = NULL;
		return (NULL);
	}
	while ((*saveptr)[i] != (*delim) && (*saveptr)[i] != '\0')
		i++;
	if ((*saveptr)[i] == '\0')
	{
		*saveptr = NULL;
	}
	else
	{
		(*saveptr)[i] = '\0';
		while ((*saveptr)[++i] == (*delim))
			;
		*saveptr = &(*saveptr)[i];
	}

	return (tok_ptr);
}
