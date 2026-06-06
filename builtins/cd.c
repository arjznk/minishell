#include "minishell.h"

void    ft_cd(char *str)
{
	char *line;

	line = ft_strchr(str, ' ');
	if(!line)
		return;
	if(chdir(line) == -1)
		printf("minishell: cd: %s: %s\n", line, strerror(errno));
}
