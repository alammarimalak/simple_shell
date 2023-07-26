#include "shell.h"

/**
 * release_path - function
 * NULL: NULL
 */
void  release_path(void)
{
	path_manager(CLEAR_PATH, NULL, NULL);
}

/**
 * print_path - function
 * NULL: NULL
 */
void  print_path(void)
{
	path_manager(PRINT_PATH, NULL, NULL);
}
/**
 * resolve_command_path - function
 * @old_path: character
 * @res: integer
 */
void resolve_command_path(char **old_path, int *res)
{
	path_manager(FIND_CMD, old_path, res);
}
