#include "shell.h"
void  release_path(void)
{
	path_manager(CLEAR_PATH, NULL, NULL);
}

void  print_path(void)
{
	path_manager(PRINT_PATH, NULL, NULL);
}

void resolve_command_path(char **old_path, int *res)
{
	path_manager(FIND_CMD, old_path, res);
}
