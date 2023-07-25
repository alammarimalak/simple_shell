#include "shell.h"
/**
 * free_n2d - fct
 * @Array: cmt
 * @n: cmt
*/
void free_n2d(char **Array, int n)
{
	int	it = 0;

	if (Array == NULL)
		return;

	while (it < n)
	{
		if (Array[it])
			free(Array[it]);

		it++;
	}

	free(Array);
}
/**
 * free_2d - fct
 * @Array: cmt
 * Return: void
*/
void free_2d(char **Array)
{
	int	it = 0;

	if (Array == NULL)
		return;

	while (Array[it])
	{
		free(Array[it]);
		it++;
	}

	free(Array);
}
/**
 * find_cmd - fct
 * @cmd_loc: cmt
 * @paths: cmt
 * @search_result: cmt
 * Return: cmt
*/
int find_cmd(char **cmd_loc, char **paths,  int *search_result)
{
	int i = 0;
	int res;
	char *copy = NULL;
	int path_size;

	res = access(*cmd_loc, X_OK);
	if (res != -1)
	{
		*search_result = 1;
		return (*search_result);
	}
	while (paths[i] != NULL)
	{
		path_size = (strlen(paths[i]) + strlen(*cmd_loc) + 2);
		copy      = (char *) malloc(path_size);
		strcpy(copy, paths[i]);
		strcat(copy, "/");
		strcat(copy, *cmd_loc);
		res = access(copy, X_OK);
		if (res != -1)
		{
			free(*cmd_loc);
			*cmd_loc = malloc(path_size);
			strcpy(*cmd_loc, copy);
			free(copy);
			*search_result = 1;
			return (*search_result);
		}
		i++;
		free(copy);
		copy = NULL;
	}
	*search_result = 0;
	return (*search_result);
}
/**
 * loginfo - fct
 * @s: cmt
*/
void loginfo(const char *s)
{
	printf("[*] %s\n", s);
}
