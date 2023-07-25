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
