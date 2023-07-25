#include "shell.h"
/**
 * map_cpy - fct
 * @m: cmt
 * @src: cmt
*/
void map_cpy(map_t *m, char **src)
{
	int it;

	for (it = 0; src[it]; it++)
		append_entry(m, src[it], NULL, NULL);

	(m)->all[(m)->size] = NULL;
}
