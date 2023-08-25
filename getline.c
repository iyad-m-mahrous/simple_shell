#include "main.h"

/**
 * _get_input - similar to getline function
 * @line: buffer containing the retrieved characters
 * @len: length of the buffer
 * @stream: File stream
 * @total_size: number of input characters including newline
 * @num_lines: number of lines separated by newline
 *
 * Return: pointer to the input string
*/
char *_get_input(char **line, size_t *len, FILE *stream, ssize_t *total_size
		, int *num_lines)
{
	ssize_t read_len = 0, i = 0, prev_total_size = 0;
	char *in_ptr = NULL, buff[BUFF_SIZE];

	do {
		prev_total_size = *total_size;
		read_len = read(fileno(stream), buff, BUFF_SIZE);
		if (read_len == 0)
			return (NULL);
		if (read_len == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		(*total_size) += read_len;
		if ((*num_lines) == 0)
			(*num_lines)++;
		in_ptr = realloc(in_ptr, sizeof(**line) * ((*total_size) + 1));
		if (!in_ptr)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}
		*len = ((*total_size) + 1);
		for (i = 0; i < read_len; i++)
		{
			if (buff[i] == ';')
				buff[i] = '\n';
			in_ptr[prev_total_size + i] = buff[i];
			if ((buff[i] == '\n') && (i != (read_len - 1)))
				(*num_lines)++;
		}
		prev_total_size = *total_size;
	} while (read_len == BUFF_SIZE);
	in_ptr[(*total_size)] = '\0';

	return (in_ptr);
}


/**
 * _getline - similar to getline function
 * @line: buffer containing the retrieved characters
 * @len: length of the buffer
 * @stream: File stream
 *
 * Return: -1 if error else the number of characters retrieved
*/
ssize_t _getline(char **line, size_t *len, FILE *stream)
{
	ssize_t total_size = 0, i = 0;
	static int num_lines;
	static char *in_ptr, *in_ptr_main;

	fflush(stdout);
	if ((*len) == 0)
		num_lines = 0;
	if (num_lines == 0)
	{
		in_ptr = _get_input(line, len, stream, &total_size, &num_lines);
		if (!in_ptr)
			return (-1);
		if (!in_ptr_main)
			in_ptr_main = in_ptr;
	}
	if (num_lines != 0)
	{
		for (i = 0; in_ptr[i] != '\n' && in_ptr[i] != '\0'; i++)
			;
		total_size = (i + 1);
		*len = total_size + 1;
		*line = realloc((*line), sizeof(**line) * (total_size + 1));
		for (i = 0; i < total_size; i++)
			(*line)[i] = in_ptr[i];
		(*line)[total_size] = '\0';
		num_lines--;
		if (num_lines == 0)
		{
			free(in_ptr_main);
			in_ptr = NULL;
			in_ptr_main = NULL;
		}
		else
			in_ptr = in_ptr + total_size;
	}
	return (total_size);
}
