#include "shell.h"

/**
 * my_cd - changes a working directory.
 * @param: pointer to paramater strings.
 * Return: 0 if success or -1 if fail.
 */
int my_cd(void **param)
{
	char **parameter = (char **)param;
	char *dir;

	if (parameter == NULL || parameter[0] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			return (-1);
		else
			return (0);
	}
	dir = parameter[0];

	if (previousDir(dir) == -1)
	{
		if (homeDir(dir) == -1)
		{
			if (chdir(dir) != 0)
			{
				perror("cd");
				return (-1);
			}
		}
	}
	if (dirUpdate() == -1)
	{
		return (-1);
	}
	return (0);
}

/**
 * previousDir - checks a command "-"
 *				and moves to previous dir.
 *@dir: string pointer to the previous dir.
 *Return: 0 for success, -1 for failure.
*/
int previousDir(char *dir)
{
	char *prevDir = getenv("OLDPWD");

	if (strcmp(dir, "-") == 0)
	{
		if (prevDir == NULL)
		{
			perror("cd: OLDPWD not set");
			return (-1);
		}
		if (chdir(prevDir) != 0)
		{
			perror("chdir");
			return (-1);
		}
		return (0);
	}
	return (-1);
}


/**
 * homeDir - check for "~" string and
 *			moves to system Home dir
 * @dir: pointer to directory string.
 * Return: 0 if success, -1 if failed.
*/
int homeDir(char *dir)
{
	char *home = getenv("HOME");

	if (strcmp(dir, "~") == 0)
	{
		if (home == NULL)
		{
			perror("Home Dir Not set \"setenv HOME hom/directory/is");
			return (-1);
		}
		if (chdir(home) != 0)
		{
			perror("homedir");
			return (-1);
		}
		return (0);
	}
	return (-1);
}

/**
 * dirUpdate - updates current, working and old directory environs.
 * Return: 0 on success, -1 on failure.
*/
int dirUpdate(void)
{
	char currentDir[MAX_CMD_LEN];

	if (getcwd(currentDir, sizeof(currentDir)) == NULL)
	{
		perror("dirUpdate");
	}
	if (setenv("OLDPWD", getenv("PWD"), 1) != 0)
	{
		perror("dirUpdate");
		return (-1);
	}
	if (setenv("PWD", currentDir, 1) != 0)
	{
		perror("dirUpdate");
		return (-1);
	}
	return (0);
}
