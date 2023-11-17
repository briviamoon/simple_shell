#include "shell.h"

/**
 * builtin_exit - Handle the builtin 'exit' command.
 * @param: An array of commands and arguments.
 * Return: 1 to indicate that the shell should exit.
 */
int builtin_exit(void **param)
{
	int state;
	char **status = (char **)param;

	if (status[0] == NULL)
		exit(0);
	else
	{
		state = atoi(status[0]);
		exit(state);
	}
	return (0);
}

/**
 * builtin_help - Display information about built-in commands.
 * @param: void unused variable.
 * Return: Always returns 1.
 */
int builtin_help(void **param)
{
	(void)param;

	printf("Built-in commands:\n");
	printf("1. exit - Terminate the shell.\n");
	printf("2. cd <directory> - Change the current directory.\n");
	printf("3. help - Display this help information.\n");
	printf("4. setenv - set an environment variable\n");

	return (1);
}
/**
 * printEnvironment - prints a systems environment.
 * @param: void casted parameter to a relative command.
 * Return: -1 if fail, 0 if success.
 */
int printEnvironment(void **param)
{
	char **env;

	(void)param;
	for (env = environ; *env != NULL; env++)
		printf("%s\n", *env);

	return (0);
}

