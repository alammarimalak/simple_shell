#include "shell.h"

unsigned int iteration_ = 1;

void increment_it()
{
	iteration_++;
}

int _exec(char **argv, char *uinput)
{
	int   pid, code, stat = 0;
	map_t *m    = get_envp_map();
	char  *shell;
	int   res;
	path_manager(FIND_CMD, &argv[0], &res);

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
		iteration_,
		argv[0]
	);

	free(shell);
	return -1;
}
