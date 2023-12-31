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

/**
 * setEnvironment - sets an environment variable.
 * @param: casted as void but accepts any type.
 * Return: 0 if successfull, -1 if success.
 *
 * Description: takes in a string in the form
 *				VARIABLE  VALUE.
 */
int setEnvironment(void **param)
{
	char **Newenviron = (char **)param;
	char *variable = NULL;
	char *value = NULL;
	struct EnvNode *envList = getEnvironment();

	if (Newenviron != NULL && Newenviron[0] != NULL && Newenviron[1] != NULL)
	{
		variable = Newenviron[0];
		value = Newenviron[1];
		printf("variable: %s && Value: %s", variable, value);
		envList = addNode(envList, variable, value);
		environ = ConvertEnvListToArray(envList);
	}
	return (0);
}

/**
 * ConvertEnvListToArray - Converts the linked list of env var to arr.
 * @envList: Pointer to the head node of the linked list.
 * Return: Array of strings representing environment variables.
 */
char **ConvertEnvListToArray(struct EnvNode *envList)
{
	int counter = 0, i;
	size_t len;
	struct EnvNode *current = envList;
	char **envArray;

	while (current != NULL)
	{
		counter++;
		current = current->Next;
	}
	envArray = (char **)malloc((counter + 1) * sizeof(char *));
	if (envArray == NULL)
	{
		perror("malloc in ConvertEnvListToArray");
	}
	current = envList;
	for (i = 0; i < counter; i++)
	{
		/*conct the vars to the values*/
		/*the extra 1 in this malloc is form the '=' sign*/
		len = (strlen(current->variable) + strlen(current->value)) + 2;
		envArray[i] = (char *)malloc(len);
		if (envArray[i] == NULL)
		{
			perror("malloc in ConvertEnvListToArray");
		}
		strcpy(envArray[i], current->variable);
		envArray[i][len] = '=';
		strcpy(envArray[i] + len + 1, current->value);
		current = current->Next;
	}
	envArray[counter] = NULL;
	return (envArray);
}
