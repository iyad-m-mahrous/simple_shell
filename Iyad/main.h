#ifndef MAIN_H
#define MAIN_H

#define BUFF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;

void env_free(char *env[]);
int env_del(int index, char *env[]);
int _setenv(char *args[], char *argv[], char *env[]
		, int *err_count, char *line);
int _unsetenv(char *args[], char *argv[], char *env[]
		, int *err_count, char *line);
int env_add(char *varname, char *varvalue, char *env[]);
int env_modify(int index, char *varname, char *varvalue, char *env[]);
int env_var_check(char *varname);
int env_check(char *args[], char *argv[], int *err_count);
int exit_check(char *args[], char *argv[], char *env[]
		, int *err_count, char *line);
char *_strtok_r(char *str, const char *delim, char **saveptr);
int _atoi(char *s);
void print_env(void);
ssize_t _getline(char **line, size_t *len, FILE *stream);
char *_get_input(char **line, size_t *len, FILE *stream, ssize_t *total_size
		, int *num_lines);
void run_command(char *line, size_t line_len, char *argv[], char *env[]);
char *get_full_path(char *command);

#endif
