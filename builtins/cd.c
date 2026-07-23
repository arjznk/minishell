#include "minishell.h"

void	ft_cd(t_exec *exec)
{
	char	*line;
	char	*cmd;
	char	*new_cmd;

	cmd = exec->tmp->args[0];
	line = exec->tmp->args[1];
	new_cmd = ft_strchr_echo(exec->tmp->args[0], 'n');
	if(ft_strcmp(cmd, "cd") == 0 || ft_strcmp(new_cmd, "cd") == 0)
	{
		if(!line)
		{
			chdir(exec->home);
			return;
		}
		if(chdir(line) == -1)
		{
			printf("minishell: cd: %s: %s\n", line, strerror(errno));
			exec->status = 1;
		}
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd);
		exec->status = 127;
	}
}
int	check_directory(t_exec *exec)
{
	struct stat	st;

	if(!((*exec->cmd)->args))
		return (0);
	if(dot_error(exec) == 1)
		return (1);
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
            printf("minishell: %s : is a directory\n", (*exec->cmd)->args[0]);
            exec->status = 126;
            return (1);
        }
    }
    return(0);
}

