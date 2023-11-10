#include "shell.h"

/**
 * main - executes a simple shell.
 * Return: always 0
 */

int main(void)
{
	char *commandLine = NULL;
	size_t commandLen = 0;
	ssize_t bytesRead;

	while (1)
	{
		/*Show Prompt Sign*/
		printf("shelly Vibe$ ");

		/*Get User Input & Deal with EOF*/
		bytesRead = getline(&commandLine, &commandLen, stdin);
		if (bytesRead == -1)
		{
			printf("\n");
			break;
		}

		/*rm New Line char*/
		if (commandLen > 0 && commandLine[commandLen - 1] == '\n')
		{
			commandLine[commandLen - 1] = '\0';
		}

		/*remove the pesky backspace symbols*/
		/*beGoneBackSpace(commandLine);*/

		/*Initiate Command Execution*/
		executioner(commandLine);
	}
	free(commandLine);
	return (0);
}

