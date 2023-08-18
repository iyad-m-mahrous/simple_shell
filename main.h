#ifndef MAIN_H
#define MAIN_H

#define BUFF_SIZE 250

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

int env_check(char *args[], char *argv[], int *err_count);
int exit_check(char *args[], char *argv[]
		, int *err_count, char *line);
char *_strtok_r(char *str, const char *delim, char **saveptr);
int _atoi(char *s);
void print_env(void);
ssize_t _getline(char **line, size_t *len, FILE *stream);
char *_get_input(char **line, size_t *len, FILE *stream, ssize_t *total_size
		, int *num_lines);
void run_command(char *line, size_t line_len, char *argv[]);
char *get_full_path(char *command);

#endif
