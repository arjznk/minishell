#include "minishell.h"

int	dot_error(t_exec *exec)
{
	char *cmd;

	cmd = (*exec->cmd)->args[0];
	if(count_dots(exec) > 1)
	{
		printf("minishell: %s: command not found\n", cmd);
		exec->status = 2;
		return (1);
	}
	else if(ft_strcmp(cmd, ".") == 0)
	{
		printf("minishell: %s: filename argument required\n%s: usage: %s filename [arguments]\n", cmd, cmd, cmd);
		exec->status = 2;
		return (1);
	}
	return (0);
}

int		count_dots(t_exec *exec)
{
	int count;
	int i;
	char *cmd;

	cmd = (*exec->cmd)->args[0];
	i = 0;
	count = 0;
	while(cmd[i])
	{
		if(cmd[i] == '.')
			count++;
		i++;
	}
	return (count);
}

void	syntax_error(char *token, t_exec *exec)
{
	printf("minishell: syntax error near unexpected token '%s'\n", token);
	exec->status = 2;
}

