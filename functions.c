#include "shell.h"

/**
 * executioner - executes the shell command
 * @commandLine: poiner to command line string.
 */

void executioner(char *commandLine)
{
	pid_t pid;
	int status;
	char **args;
	char command[100];

	args = malloc((MAX_CMD_LEN + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("MAlloc args Fail: ");
		exit(EXIT_FAILURE);
	}

	args = tokenize(commandLine, args);
	if (*args[0] != '/')
	{
		strcpy(command, "/bin/");
		strcat(command, args[0]);
	}
	else
	{
		strcpy(command, args[0]);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("forking gone wrong: ");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/*printf("Executing Command: %s\n\n", args[0]);*/
		/*Start the child process*/

		if (execve(command, args, environ) == -1)
		{
			perror("shelly bad vibe$ ");
			printf("errno: %d\n\n", errno);
			exit(EXIT_FAILURE);
		}
		/*printf("Child Process Exected Successfully\n\n");*/
		exit(EXIT_SUCCESS);
	}
	else
	{
		/*Parrent Waits*/
		waitpid(pid, &status, 0);
		/*printf("Child Processes Exited\n");*/
	}
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
 */

char **tokenize(char *commandLine, char **args)
{
	char *token;
	int i = 0;

	token = strtok(commandLine, " ");

	while (token != NULL && i < MAX_CMD_LEN)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
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

