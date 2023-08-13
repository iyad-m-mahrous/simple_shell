#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

ssize_t _getline(char **line, size_t *len, FILE *stream);
void print_env(char *env[]);
void run_command(char *line, size_t line_len, char *command_name);

#endif
