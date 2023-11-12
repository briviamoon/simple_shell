#include "shell.h"

/**
 * executioner - executes the shell command
 * @commandLine: poiner to command line string.
 */

void executioner(char *commandLine)
{
	char **args;
	char command[100];
	int builtinVerified;
	int argc = 0;

	args = malloc((MAX_CMD_LEN + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("MAlloc args Fail: ");
		exit(EXIT_FAILURE);
	}

	args = tokenize(commandLine, args, argc);
	if (*args[0] != '/')
	{
		strcpy(command, "/bin/");
		strcat(command, args[0]);
	}
	else
	{
		strcpy(command, args[0]);
	}

	builtinVerified = handlerPicker(command, args, argc);
	if (builtinVerified == 0)
	{
		exit(EXIT_SUCCESS);
	}

	letsForkIt(command, args);

	free(args);
}

/**
 * beGoneBackSpace - Removes backspace symbols
 * @c: poiner to command line
 */

void beGoneBackSpace(char *c)
{
	size_t len = strlen(c);
	size_t i, j;

	for (i = 0; i < len; i++)
	{
		if (c[i] == '\b')
		{
			if (i > 0)
			{
				for (j = i - 1; j < len; j++)
				{
					c[j] = c[j + 1];
				}
				--i;
				--len;
			}
		}
	}
}

/**
 * tokenize - Splits a string into tokens.
 * @commandLine: String to be tokenized.
 * @args: An array to store the tokens
 * Return: A double pointer tothe tokens
 *		argCount Is incremented.
 */

char **tokenize(char *commandLine, char **args, int argCount)
{
	char *token;
	int i = 0;

	token = strtok(commandLine, " ");

	while (token != NULL && i < MAX_CMD_LEN)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
		argCount++;
	}
	args[i] = NULL;

	return (args);
}

/**
 * sanitize - remove non-printable char from string
 * @str: String to be sanitized
 * @unwantedChar: Character to be removed from the string
 */
void sanitize(char *str, char unwantedChar)
{
	size_t i;
	size_t len = strlen(str);

	for (i = 0; i < len; i++)
	{
		if (str[i] == unwantedChar)
		{
			str[i] = ' ';
		}
	}
}

/**
 * letsForkIt - creates a child process.
 * @command: the command to be executed.
 * @par: list of command line paramenters.
 */

void letsForkIt(char *command, char **par)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("forking gone wrong\n");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*Start execution*/
		if (execve(command, par, environ) == -1)
		{
			perror("shelly got bad vibes$ ");
			printf("errno: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		/*printf("Child Process Execution success\n");*/
		exit(EXIT_SUCCESS);
	}
	else
	{
		/*Parrent Waits For Child Process*/
		waitpid(pid, &status, 0);
		/*printf("Child Process Exited\n");*/
	}
}
