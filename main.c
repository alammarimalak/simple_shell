#include "shell.h"

void shell(void);
/**
 * main - function
 * Return: 0 if success
*/
int main(void)
{
	shell();
	return (0);
}
/**
 * shell - function
*/
void shell(void)
{
	size_t size_of_buff = 0;
	int    read_        = 0;
	char   *buff        = { 0 };
	char   **tokens     = NULL;
	bool   loop         = false;

	env_manager(INIT_ENV, NULL, NULL);
	init_path();
	loop = (isatty(STDIN_FILENO) == 1);

	do {
		if (loop)
			prompt_user();
		read_ = _getline(&buff, &size_of_buff, STDIN_FILENO);
		if (read_ <= 1)
		{
			if (buff)
			{
				free(buff);
				buff = NULL;
			}
			if (read_ == 1)
			{
				increment_it();
				continue;
			}
			if (read_ == -1 || read_ == INTRPT)
				break;
		}

		terminate_incoming_str(buff, &read_);
		read_ = trim(&buff);
		if (read_ > 0)
		{
			tokens = parse_command(buff);
			if (strcmp(tokens[0], "exit") == 0)
			{
				free_2d(tokens);
				tokens = NULL;
				break;
			}
			if (strcmp(tokens[0], "path") == 0)
				print_path();
			else if (strcmp(tokens[0], "env") == 0)
				print_env();
			else
				_exec(tokens, buff);
		}

		free_2d(tokens);

		if (buff)
			free(buff);
		buff   = NULL;
		tokens = NULL;
		increment_it();
	} while (loop || (read_ >= 0));

	release_path();

	if (buff != NULL)
		free(buff);

	deinit_env_map();
	free_2d(tokens);
}
