#include "shell.h"

int state_manager(state_action_t a)
{
	static int line_index;
	switch(a)
	{
		case INIT: {
			line_index = 0;
		} break;
		case GET: {
			return (line_index);
		} break;
		case INC: {
			line_index++;
		} break;
		case SET: {} break;
	}

	return (0);
}

int _exec(char **argv, char *uinput)
{
	int   pid, code, stat = 0;
	map_t *m    = get_envp_map();
	char  *shell;
	int   res;
	
	resolve_command_path(&argv[0], &res);

	if(res)
	{
		pid = fork();
		if(pid == 0)
		{
			/* Child Process. */
			code = execve(argv[0], argv, m->all);

			if(code == -1) 
			{
				perror("[ERROR]");
				free_2d(argv);
				free_n2d(m->keys, m->size);
				free_n2d(m->values, m->size);
				free_n2d(m->all, m->size);
				free(m);
				release_path();
				free(uinput);
				exit(1);
			}

			exit(code);
		}

		wait(&stat);
		if(WIFEXITED(stat)) 
		{
			code = WEXITSTATUS(stat);
			return code;
		}

		return -2;
	}

	shell = _get_env("_");

	printf("%s: %i: %s: not found\n", 
		shell, 
		state_manager(GET),
		argv[0]
	);

	free(shell);
	return -1;
}
