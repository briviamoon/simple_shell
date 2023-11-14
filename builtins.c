#include "shell.h"

/**
 * builtin_exit - Handle the builtin 'exit' command.
 * @commands: An array of commands and arguments.
 * Return: 1 to indicate that the shell should exit.
 */
int builtin_exit(char *commands[])
{
	if (commands[1] != NULL)
	{
		int exit_code = atoi(commands[1]);

		exit(exit_code);
	}
	exit(0);
}

/**
 * builtin_cd - Handle built-in 'cd' command
 * @commands: An array of commands and arguments.
 * Return: 1 if 'cd' command was executed successfully, 0 otherwisw.
 */
int builtin_cd(char *commands[])
{
	if (commands[1] == NULL)
	{
		fprintf(stderr, "cd: missing\n");
		return (0);
	}

	if (chdir(commands[1]) == -1)
	{
		perror("cd");
		return (0);
	}

	return (1);
}

/**
 * is_builtin - Check if a command is a built-in command.
 * @command: The command to check.
 * Return: 1 if it's a built-in command, 0 otherwise.
 */
int is_builtin(char *command)
{
	if (strcmp(command, "exit") == 0 || strcmp(command, "cd") == 0)
	{
		return (1);
}
return (0);
}

/**
 * builtin_help - Display information about built-in commands
 * Return: Always returns 1.
 */
int builtin_help(void)
{
	printf("Built-in commands:\n");
	printf("1. exit - Terminate the shell.\n");
	printf("2. cd <directory> - Change the current directory.\n");
	printf("3. help - Display this help information.\n");
	return (1);
}
