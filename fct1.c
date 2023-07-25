#include "shell.h"
volatile sig_atomic_t got_interrupted = 0;
/**
 * handle_signal - fct
 * @signal: cmt
*/
void handle_signal(int signal)
{
	if (signal == SIGINT)
	{
        got_interrupted = 1;
		}
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
	int    consume  = 1;
	size_t it       = 0;
	int    nread    = 0;
	char c;
	struct sigaction sa;

	*size = 16;
	*buff = malloc(*size);
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	while(consume)
	{
		if (it == *size - 2)
		{
			*size *= 2;
			*buff = realloc(*buff, *size);
			if (buff == NULL)
			{
				fprintf(stderr, "realloc failed to reallocate new buffer\n");
				return -1;
			}
		}

		if ((nread = read(fd, &c, 1)) <= 0) break;
		switch(c)
		{
			case '\n': {
				(*buff)[it] = 0;
				consume = 0;
				it++;
			} break;
			case '\r': {
			} break;
			case EOF: {
				return -1;
			} break;
			case SEQ_START_BYTE: {
				printf("started sequence..\n");
			} break;
			default: {
				(*buff)[it] = c;
				it++;
			} break;
		}
	}
	
	if (it == 0 && nread == 0)
		return -1;

	if (got_interrupted)
		return INTRPT;

	return it;
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
		printf("[%d] => |%s|\n", it, Array[it]);
		it++;
	}
}

