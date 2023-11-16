#include "shell.h"

/**
 * my_setenv - sets an environment avariable.
 * @param: pointer to enviroment parameter string
 *				separated by a space.
 * Return: 0 if success, -1 if failure.
 */
int my_setenv(void **param)
{
	char **parameters = (char **)param;

	if (parameters == NULL || parameters[0] == NULL || parameters[1] == NULL)
	{
		return (-1);
	}
	if (ifEnvironExist(parameters) == 0)
	{
		return (0);
	}
	else
	{
		if (addNewEnviron(parameters) == -1)
		{
			return (-1);
		}
	}
	return (0);
}

/**
 * ifEnvironExist - checks if the environment variable exists.
 *					If true, It replaces the variables value with new value
 * @parameters: pointer to an array of environment var and value
 *				strings Seperated by a space "VAR" "VALUE"
 * Return: 0 if success, -1 if failur
 */
int ifEnvironExist(char **parameters)
{
	int i;
	char *newEnvVar;
	size_t l, m;
	/*Check if var exists*/
	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], parameters[0], strlen(parameters[0])) == 0)
		{
			l = strlen(parameters[0]);
			m = strlen(parameters[1]);
			/*already exists, update value*/
			newEnvVar = malloc(l + m + 2);
			if (newEnvVar == NULL)
			{
				perror("Memory allocation error");
				return (-1);
			}

			/*Concat var-name, '=', and value*/
			strcpy(newEnvVar, parameters[0]);
			strcat(newEnvVar, "=");
			strcat(newEnvVar, parameters[1]);

			/*Replace old variable*/
			environ[i] = newEnvVar;
			return (0);
		}
	}
	return (-1);
}

/**
 * addNewEnviron - adds a new environ var
 * @parameters: pointer to strings of VAR and VALUE.
 * Return: 0 if success and -1 if failure.
 */
int addNewEnviron(char **parameters)
{
	char **newEnviron;
	char *newEnvVar;
	int envVarCount = 0, i;

	/*Variable does not exist, create a new one and count exirsting*/
	while (environ[envVarCount] != NULL)
	{
		envVarCount++;
	}
	/*Allocate mem for new var array*/
	newEnviron = (char **)malloc((envVarCount + 2) * sizeof(char *));
	if (newEnviron == NULL)
	{
		perror("Memory allocation error");
		return (-1);
	}
	/*Copy existing environment variables to the new array*/
	for (i = 0; i < envVarCount; i++)
	{
		newEnviron[i] = environ[i];
	}
	/*Create the new environment variable string*/
	newEnvVar = (char *)malloc(strlen(parameters[0]) + strlen(parameters[1]) + 2);
	if (newEnvVar == NULL)
	{
		perror("Memory allocation error");
		free(newEnviron);
		return (-1);
	}
	/*Concatenate var name, '=', & value*/
	strcpy(newEnvVar, parameters[0]);
	strcat(newEnvVar, "=");
	strcat(newEnvVar, parameters[1]);
	/*Add the new environment variable to the array*/
	newEnviron[envVarCount] = newEnvVar;
	newEnviron[envVarCount + 1] = NULL;
	environ = newEnviron;
	return (0);
}
