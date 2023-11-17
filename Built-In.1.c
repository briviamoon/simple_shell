#include "shell.h"

/**
 * handlerPicker - chooses function to execute a command.
 * @command: pointer to the command to be evaluated.
 * @args: list of command line arguments.
 * Return: 0 if the command is handled, -1 otherwise.
 */
int handlerPicker(char *command, char **args)
{
	int i = 0;
	char **param = parameterize(args);

	BuiltInCommand builtIn[] = {
		{"cd", my_cd},
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"pwd", directoryPrint},
		{"env", printEnvironment},
		{"setenv", my_setenv},
		{NULL, NULL},
	};

	if (param == NULL)
	{
		perror("malloc in handlerPicker");
		exit(EXIT_FAILURE);
	}

	for (i = 0; builtIn[i].cmdName != NULL; i++)
	{
		/*compare witht the built in commands*/
		if (strcmp(command, builtIn[i].cmdName) == 0)
		{
			/*match found, call handler function*/
			if (builtIn[i].handler((void **)param) != 0)
			{
				fprintf(stderr, "Error Executing: %s\n", command);
				return (-1);
			}
			return (0);
		}
	}
	free(param);
	return (-1);
}

/**
 * directoryChange - executed a cd command.
 * @param: poiner to command.
 * Return:always 0
 */
int directoryChange(void **param)
{
	char **dir = (char **)param;

	if (dir == NULL)
	{
		chdir("./");
		return (0);
	}
	else if (chdir(dir[0]) == -1)
	{
		printf("%s\n", dir[0]);
		perror("chdir\n");
	}
	return (0);
}

/**
 * directoryPrint - prints current working directory.
 * @param: void unused parameter.
 * Return: 0 on success, -1 on failure.
 */
int directoryPrint(void **param)
{
	char buffer[MAX_CMD_LEN];
	(void)param;

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		printf("%s\n", buffer);
	}
	else
	{
		perror("getcwd");
		return (-1);
	}
	return (0);
}

/**
 * parameterize - create a seperate array of parameters
 * And assugnes them to param.
 * @args: list of paramaters.
 * Return: pointer to an array of pointers to strings.
 */
char **parameterize(char **args)
{
	int i = 0, len = 0;
	char **param;

	while (args[len] != NULL)
	{
		len++;
	}

	param = (char **)malloc((len + 1) * sizeof(char *));
	if (param == NULL)
	{
		perror("malloc in parametizer");
		return (NULL);
	}

	while (args[i + 1] != NULL)
	{
		param[i] = args[i + 1];
		i++;
	}
	param[i] = NULL;
	return (param);
}
