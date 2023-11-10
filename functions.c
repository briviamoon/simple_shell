#include "shell.h"
extern char **environ;

/**
 * executioner - executes the shell command
 * @commandLine: poiner to command line string.
 */

void executioner(char *commandLine)
{
	pid_t pid;
	int status;
	char **args;

	args = malloc((MAX_CMD_LEN + 1) * sizeof(char *));
	if (args == NULL)
	{
		perror("MAlloc args Fail: ");
		exit(EXIT_FAILURE);
	}
	args = tokenize(commandLine, args);

	pid = fork();

	if (pid == -1)
	{
		perror("forking gone wrong: ");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("Executing Command: %s\n", args[0]);
		/*Start the child process*/

		if (execve(args[0], args, environ) == -1)
		{
			perror("shelly no bad vibe$ ");
			printf("errno: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		/*Parrent Waits*/
		waitpid(pid, &status, 0);
		printf("Child Processes Exited\n");
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
 * tokenize - tokenizes a string.
 * @c: poiner to a sting
 * Return: pointer to a pointer to string
 */

char** tokenize(char *commandLine, char **args)
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

