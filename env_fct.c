#include "shell.h"
/**
 * env_manager - fct
 * @action: cmt
 * @key: cmt
 * @value: cmt
 * Return: null
*/
void *env_manager(env_action_t action, const char *key, const char *value)
{

	static map_t *env_map;

	switch (action)
	{
		case PRINT_ENV: {
			print_env_internal(env_map);
			return (NULL);
		} break;
		case INIT_ENV: {
			env_map = create_map(ENV_MAX);
			map_cpy(env_map, environ);
		} break;
		case SET_ENTRY: {
			set_value(env_map, key, value);
		} break;
		case GET_VALUE: {
			return (get_value(env_map, key));
		} break;
		case GET_KEYS: {
			return (env_map->keys);
		} break;
		case DELETE_ENTRY: {
			printf("UNREACHABLE, not implemented..\n");
		} break;
		case CLEAR_ENV: {
			distroy_map(env_map);
		} break;
		case GET_MAP: {
			return (env_map);
		} break;
		default:
			printf("UNREACHABLE.\n");
			break;
	}

	return (NULL);
}
/**
 * deinit_env_map - fct
*/
void deinit_env_map(void)
{
	env_manager(
		CLEAR_ENV,
		NULL,
		NULL
	);
}
/**
 * _get_env - fct
 * @key: cmt
 * Return: env
*/
char *_get_env(const char *key)
{
	return ((char *) env_manager(
		GET_VALUE,
		key,
		NULL
	));
}
/**
 * _set_env - fct
 * @key: cmt
 * @value: cmt
*/
void _set_env(const char *key, const char *value)
{
	env_manager(
		SET_ENTRY,
		key,
		value
	);
}
