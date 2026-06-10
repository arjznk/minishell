#include "minishell.h"

void    ft_cd(char *str)
{
	char *line;
	char *cmd;

	line = ft_strchr(str, ' ');
	cmd = search_and_stop(str, ' ');
	if(ft_strcmp(cmd, "cd") == 0)
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
