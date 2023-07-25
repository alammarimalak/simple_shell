#include "shell.h"
/**
 * print_env - fct
*/
void print_env(void)
{
	env_manager(PRINT_ENV, NULL, NULL);
}
/**
 * print_env_internal - fct
 * @m: cmt
*/
void print_env_internal(map_t *m)
{
	char **env = m->all;
	int iterator = 0;

	for (; env[iterator] != NULL; iterator++)
		fprintf(stdout, "%s\n", env[iterator]);
}
/**
 * get_envp_map - fct
 * Return: env
*/
map_t *get_envp_map(void)
{
	return ((map_t *) env_manager(GET_MAP, NULL, NULL));
}
