#include "shell.h"

/**
 * my_strtok - Tokenizes a string.
 * @str: pointer to string to tokenize.
 * @delim: delimiter.
 * Return: returns pointer to a string without the delimiter
 */
char *my_strtok(char *str, char delim)
{
	static char *lastToken; /*Keeps track of the last token*/
	char *tokenStart;

	/*If a new string provided, update lastToken*/
	if (str != NULL)
	{
		lastToken = str;
	}
	else if (lastToken == NULL)
	{
		/*If !string && lastToken = NULL*/
		return (NULL);
	}
	/*Find next occurrence of the delim*/
	tokenStart = lastToken;
	while (*lastToken != '\0' && *lastToken != delim)
	{
		lastToken++;
	}
	/*If delim found, replace with null char*/
	if (*lastToken == delim)
	{
		*lastToken = '\0';
		lastToken++;
	}
	else
	{
		/*If end of string, update lastToken to NULL*/
		lastToken = NULL;
	}
	return (tokenStart);
}
