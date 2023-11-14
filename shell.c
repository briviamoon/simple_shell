#define _GNU_SOURCE
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
	char *shelly = "Shelly Vibe$";
	/*char *hardTest = "/bin/ls";*/

	setenv("TERM", "xterm-256color", 1);
	setEnvironment()

	while (1)
	{
		/*Show Prompt Sign*/
		printf("%s ", shelly);

		/*Get User Input & Deal with EOF*/
		bytesRead = getline(&commandLine, &commandLen, stdin);
		if (bytesRead != -1)
		{
			/*rm New Line char*/
			if (commandLen > 0 && commandLine[commandLen - 1] == '\n')
			{
				commandLine[commandLen - 1] = '\0';
			}

			/*Remove unwanted chars from string*/
			sanitize(commandLine, '\n');

			/*remove the pesky backspace symbols*/
			/*beGoneBackSpace(commandLine);*/

			/*Initiate Command Execution*/
			executioner(commandLine);
			/*printf("The HardTest\n");*/
			/*executioner(hardTest);*/
		}
		else
		{
			printf("\n");
			break;
		}
	}
	free(commandLine);
	return (0);
}
