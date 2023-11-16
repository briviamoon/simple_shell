#include "shell.h"

/**
 * my_getline - read input from a stream.
 * @line: address to pointer to line buffer.
 * @len: address to buffer length.
 * @stream: input source.
 * Return: -1 if fail, 0 if success.
 */
size_t my_getline(char **line, size_t *len, FILE *stream)
{
	int c;
	size_t i = 0;

	if (!line || !len)
		return (-1);
	/*set default buf size if not provided*/
	if (*line == NULL || *len == 0)
	{
		*len = MAX_CMD_LEN;
		*line = (char *)malloc(*len);
		if (*line == NULL)
		{
			perror("malloc my_getline error");
			return (-1);
		}
	}
	while ((c = getc(stream)) != EOF && c != '\n')
	{
		(*line)[i++] = (char)c;
		/* dynamic resize of buffer if needed*/
		if (i == *len - 1)
		{
			*len *= 2;
			*line = (char *)realloc(*line, *len);
			if (*line == NULL)
			{
				perror("realloc in my_getline error");
				return (-1);
			}
		}
	}
	/*Check if any char was read*/
	if (i == 0 && c == EOF)
		return (-1);

	(*line)[i] = '\0';
	return (i);
}
