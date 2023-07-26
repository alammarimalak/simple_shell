#include "shell.h"
/**
 * prompt_user - fct
*/
void prompt_user(void)
{
	int it = 0;

	while (SHELL_HEADER[it])
		_putchar(SHELL_HEADER[it++]);

	_putchar('#');
	_putchar(' ');
}
/**
 * print_2d - fct
 * @Array: cmt
*/
void print_2d(char **Array)
{
	int it = 0;

	if (Array == NULL)
		return;

	while (Array[it])
	{
		printf("%s\n", Array[it]);
		it++;
	}
}

