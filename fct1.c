#include "shell.h"
/**
 * signal_manager - fct
 * @a: cmt
 * Return: void
*/
int signal_manager(state_action_t a)
{
	static sig_atomic_t got_interrupted;

	switch (a)
	{
		case INIT: {
			got_interrupted = 0;
		} break;
		case GET: {
			return (got_interrupted);
		} break;
		case SET: {
			got_interrupted = 1;
		} break;
		default:
			break;
	}

	return (0);
}

/**
 * handle_signal - fct
 * @signal: cmt
*/
void handle_signal(int signal)
{
	if (signal == SIGINT)
		signal_manager(SET);
}
/**
 * match_char - fct
 * @c: cmt
 * @buff: cmt
 * @idx: cmt
 * Return: tmp or idx
*/
int match_char(char c, char *buff, int *idx)
{
	int tmp = *idx;

	switch (c)
	{
		case '\n': {
			buff[tmp] = 0;
			tmp++;
			*idx = tmp;
			return (*idx - *idx);
		} break;
		case '\r': {
		} break;
		case EOF: {
			return (-1);
		} break;
		default: {
			buff[tmp] = c;
			tmp++;
			*idx = tmp;
			return (*idx - *idx + 1);
		} break;
	}

	return (tmp);

}
/**
 * _getline - fct
 * @buff: cmt
 * @size: cmt
 * @fd: cmt
 * Return: value
*/
int _getline(char **buff, size_t *size, int fd)
{
	int    consume = 1, nread = 0, it = 0, res;
	char c;
	struct sigaction sa;

	*size = 16;
	*buff = malloc(*size);
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal_manager(INIT);

	while (consume)
	{
		if ((size_t)it == *size - 2)
		{
			*size *= 2;
			*buff = realloc(*buff, *size);
			if (buff == NULL)
			{
				fprintf(stderr, "realloc failed to reallocate new buffer\n");
				return (-1);
			}
		}
		nread = read(fd, &c, 1);
		if (nread <= 0)
			break;
		res = match_char(c, *buff, &it);
		if (res == -1)
			return (-1);
		consume = res;
	}

	if (it == 0 && nread == 0)
		return (-1);

	if (signal_manager(GET))
		return (INTRPT);

	return (it);
}
/**
 * _putchar - fct
 * @c: char
 * Return: char
*/
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
