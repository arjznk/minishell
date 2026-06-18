#include "minishell.h"

void    ft_cd(t_exec *exec)
{
	char *line;
	char *cmd;
	char *new_cmd;

	cmd = (*exec->cmd)->args[0];
	line = (*exec->cmd)->args[1];
	new_cmd = ft_strchr_echo((*exec->cmd)->args[0], 'n');
	if(ft_strcmp(cmd, "cd") == 0 || ft_strcmp(new_cmd, "cd") == 0)
	{
		if(!line)
			return;
		if(chdir(line) == -1)
			printf("minishell: cd: %s: %s\n", line, strerror(errno));
	}
	else
		printf("minishell: %s: command not found\n", cmd);
}

/*
si creer dossier, ensuite entrer dans le dossier, le supp et faire un cd .. 
se baser sur le $OLDPWD pour se reperer

*/
