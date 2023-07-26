#include "shell.h"

/**
 * path_manager - fct
 * @cmd_loc: char
 * @res: integer
 * @action: char
 */
void path_manager(path_action_t action, char **cmd_loc, int *res)
{
	static char **path_;

	switch (action)
	{
		case PRINT_PATH: {
					 print_2d(path_);
				 } break;
		case INIT_PATH: {
					path_ = get_tokenized_path();
				} break;
		case FIND_CMD: {
				       find_cmd(cmd_loc, path_, res);
			       } break;
		case CLEAR_PATH: {
					 free_2d(path_);
				 } break;
		default:
		printf("UNREACHABLE.! `path_man`\n");
		break;
	}
}

/**
 * find_cmd - fct
 * @cmd_loc: cmt
 * @paths: cmt
 * @result_: cmt
 */
void find_cmd(char **cmd_loc, char **paths, int *result_)
{
	int i = 0;
	int res;
	char *copy = NULL;
	int path_size;

	res = access(*cmd_loc, X_OK);

	if (res != -1)
	{
		*result_ = 1;
		return;
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
			*result_ = 1;
			return;
		}

		i++;
		free(copy);
		copy = NULL;
	}

	*result_ = 0;
}

/**
 * _getpath - getpath function
 * Return: path
 */
char *_getpath()
{
	char *path   = _get_env("PATH");

	if (!path)
	{
		puts("PATH env was not found!.\n");
		exit(1);
	}

	return (path);
}

/**
 * get_tokenized_path - get tokenized path function
 * Return: NULL or out
 */
char **get_tokenized_path()
{
	char *path     = _getpath();
	char **out;

	if (!path)
		return (NULL);

	out = split_by_delim(path, ":");
	free(path);
	return (out);
}

/**
 * init_path_manager - init path manager function
 */
void init_path_manager(void)
{
	path_manager(INIT_PATH, NULL, NULL);
}

