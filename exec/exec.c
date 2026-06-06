#include "minishell.h"

void	ft_exec(t_path *path, char **argv, char **envp)
{
	// char *line;

	(void)path;
	// line = ft_strchr(argv[1], ' ');
	execve("/usr/bin/ls", argv, envp);

}

/*
fork, quand l'id est 0 -> processus enfant
*/