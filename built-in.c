#include "shell.h"

/**
 * handlerPicker - chooses function to execute a command.
 * @command: pointer to the command to be evaluated.
 * @args: list of command line arguments.
 * @argc: number of arguments.
 * Return: 0 if the command is handled, -1 otherwise.
 */

int handlerPicker(char *command, char **args, int argc)
{
	int i;
	char **param = (char **)malloc(sizeof(char *) * (argc + 1));

	struct BuiltInCommand builtIn[] = {
		{"cd", directoryChange},
		{"echo", stringEcho},
		{NULL, NULL}};

	if (param == NULL)
	{
		perror("malloc in handlerPicker");
		exit(EXIT_FAILURE);
	}

	parameterize(param, args);

	for (i = 0; builtIn[i].cmdName != NULL; i++)
	{
		/*compare witht the built in commands*/
		if (strcmp(command, builtIn[i].cmdName) == 0)
		{
			/*match found, call handler function*/
			if (strcmp(command, "pwd") == 0)
			{
				directoryPrint();
			}
			if (builtIn[i].handler((void *)param[i]) != 0)
			{
				printf("something's of in a built in handler\n");
				perror("handler function\n");
			}
			return (0);
		}
	}
	free(param);
	return (-1);
}

/**
 * directoryChange - executed a cd command.
 * @cmd: poiner to command.
 * Return:always 0
 */
int directoryChange(void *param)
{
	char *dir = (char *)param;

	if (chdir(dir) != 0)
	{
		perror("chdir");
	}
	return (0);
}

void directoryPrint()
{
	char buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
	{
		printf("%s\n", buffer);
	}
	else
	{
		perror("getcwd");
	}
}

/**
 * stringEcho - prints echo argument to stdout.
 * @param: string to print.
 * Return: always 0.
 */
int stringEcho(void *param)
{
	char *str = (char *)param;
	if (str != NULL)
	{
		printf("echoing Haloo...\n\n");
		sanitize(str, '\"');
		printf("%s", str);
	}
	return (0);
}

/**
 * parameterize - create a seperate array of parameters
 * And assugnes them to param.
 * @args: list of paramaters.
 * @param: poiner to add args to.
 */
void parameterize(char **param, char **args)
{
	int i = 0;

	while (args[i] != NULL)
	{
		param[i] = args[i + 1];
		i++;
	}
}
