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
#include <ctype.h>
#define MAX_CMD_LEN 150

extern char **environ;
void executioner(char *commandLine);
void beGoneBackSpace(char *c);
char **tokenize(char *commandLine, char **args, int argCount);
void sanitize(char *str, char unwantedChar);
void letsForkIt(char *command, char **par);
int commandExists(char *cmd);

/*
 * BuiltInCommand - Data structure for built in commands.
 * @cmdName: name of command.
 * @handler: function to handle the command.
 */
struct BuiltInCommand {
	char *cmdName;
	int (*handler)(void *param);
};

/*built in commands functions*/
int handlerPicker(char *command, char **args, int argc);
int directoryChange(void *param);
void directoryPrint();
int stringEcho(void *param);
void parameterize(char **param, char **args);

/**
 * EnvironmentNode - Structure of linked-list of environment vars.
 * @variable: environment variable.
 * @Value: value of the environment variable.
 */
struct EnvNode {
	char *variable;
	char *value;
	struct EnvNode *Next;
};

/*Node Related functions*/
void addNode(struct EnvNode *head, char *variable, char *value);
void freeTheNodes(struct EnvNode *head);
char *findEnvVariable(struct EnvNode *head, char *variable);
struct EnvNode* getEnvironment();

#endif
