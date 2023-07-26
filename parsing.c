#include "shell.h"
/*
 * trim-function that trims a chain of characters
 * s: pointer for the function
 * Return: if success
 */

int trim(char **s)
{
	char   *tmp  = *s;
	size_t it  = 0;
	int    len = strlen(*s);
	char   *buff = malloc(len + 1);

	if (tmp == NULL || buff == NULL)
		return (0);

	if (!isspace(*tmp))
	{
		free(buff);
		return (len);
	}

	while (isspace(*tmp))
		tmp++;

	while (*tmp)
		buff[it++] = *tmp++;

	buff[it] = '\0';

	free(*s);

	*s = buff;
	return (it);
}

/*
 * terminate_incoming_str - function
 * s: pointer for the function
 */

void terminate_incoming_str(char *s, int *size)
{
	if (*size >= 2)
	{
		if (s[*size - 2] == '\r')
		{
			s[*size - 2] = 0;
			*size -= 1;
			return;
		}

		s[*size - 1] = 0;
		*size -= 1;
	}
}
/*
 * **split_by_delim - function that splits by delimiter
 * *buffer: pointer
 * *delim: delimiter pointer
 * Return: return tokens
 */
char **split_by_delim(const char *buffer, const char *delim)
{
	int  cap = 12;
	int  it  = 0;

	char *tmp = { 0 };
	char **tokens = malloc(sizeof(char *) * cap);
	char *bcopy   = malloc(strlen(buffer) + 1);

	bcopy = strcpy(bcopy, buffer);
	tmp   = strtok(bcopy, delim);

	while (tmp != NULL)
	{
		if (it == cap - 1)
		{
			tokens = realloc(tokens, sizeof(char *) * cap * 2);
			cap *= 2;
		}

		(tokens)[it] = malloc(strlen(tmp) + 1);
		(tokens)[it] = strcpy((tokens)[it], tmp);
		tmp          = strtok(NULL, delim);
		it++;

	}


	tokens     =  realloc(tokens, sizeof(char *) * (it + 1));
	tokens[it] =  NULL;
	free(bcopy);

	return (tokens);
}

char **parse_command(char *buff)
{
	return (split_by_delim(buff, " \t\n"));
}
