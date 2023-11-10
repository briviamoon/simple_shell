#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_CMD_LEN 150

void executioner(char *commandLine);
void beGoneBackSpace(char *c);
char** tokenize(char *commandLine, char **args);

#endif
