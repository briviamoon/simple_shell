#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
/*#include <shell.h>*/	 /*This is in use on case of a linux system*/
/*#include <windows.h>*/ /*This is in use in case of a windows system*/
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <stdbool.h>
#define EXEC_FAILURE 777
#define FORK_FAILURE 555
#define MAX_CMD_LEN 1024
#define EXEC_FAILURE 777
#define FORK_FAILURE 555

extern char **environ;
void executioner(char *commandLine);
char **tokenize(char *commandLine, char **args, int argCount);
void sanitize(char *str, char unwantedChar);
void letsForkIt(char *command, char **par);
char **parameterize(char **args);
int builtin_help(void **param);
size_t my_getline(char **line, size_t *len, FILE *stream);
char *my_strtok(char *str, char delim);
int addNewEnviron(char **parameters);
int ifEnvironExist(char **parameters);
int previousDir(char *dir);
int homeDir(char *dir);
int dirUpdate(void);
bool findCommandInPath(char *command, char *result);

/**
 * struct BuiltInCommand - Data structure for built in commands.
 * @cmdName: name of command.
 * @handler: function to handle the command.
 *
 * Description: Structure containing a command signature
 *				And a Relative Function Call to execute it.
 */
typedef struct BuiltInCommand
{
	char *cmdName;
	int (*handler)(void **param);
} BuiltInCommand;

/*built in commands functions*/
int handlerPicker(char *command, char **args);
int directoryChange(void **param);
int directoryPrint(void **param);
int builtin_exit(void **param);
int printEnvironment(void **param);
int setEnvironment(void **param);
int my_setenv(void **param);
int my_cd(void **param);

#endif
