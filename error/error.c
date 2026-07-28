#include "minishell.h"

void	cmd_error(t_exec *exec)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(exec->tmp->args[0], 2);
    ft_putendl_fd(": command not found", 2);
    exec->status = 127;
    close_files(exec);
    if(exec->old_fd != -1)
        close(exec->old_fd);
    close(STDIN_FILENO);
    free_all(exec);
    exit(127);
}

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

int	check_directory(t_exec *exec)
{
	struct stat	st;

	if(!((*exec->cmd)->args))
		return (0);
	if(c_strcmp((*exec->cmd)->args[0], '/') == 0)
	{
		if(stat((*exec->cmd)->args[0], &st) == -1)
		{
			printf("minishell: %s : %s\n", (*exec->cmd)->args[0], strerror(errno));
			exec->status = 127;
			return(1);
		}
		if(S_ISDIR(st.st_mode))
		{
			printf("minishell: %s : Is a directory\n", (*exec->cmd)->args[0]);
			exec->status = 126;
			return (1);
		}
	}
	if(dot_error(exec) == 1)
		return (1);
    return(0);
}