#include "shell.h"

/**
 * findCommandInPath - search for a command in the PATH
 * @command: command to search for.
 * @result: buffer to store full path of command if found.
 * Return: true if fount, false otherwise.
 */
bool findCommandInPath(char *command, char *result)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = my_strtok(path_copy, ':');

	while (dir != NULL)
	{
		/*if path exists in curr dir*/
		sprintf(result, "%s/%s", dir, command);
		if (access(result, X_OK) == 0)
		{
			free(path_copy);
			return (true);
		}

		dir = my_strtok(NULL, ':');
	}
	free(path_copy);
	return (false);
}

