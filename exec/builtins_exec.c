#include "minishell.h"

void	execute_builtins(t_exec *exec)
{
    if(ft_strcmp(exec->tmp->args[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(exec->tmp->args[0], "exit") == 0)
        ft_exit(exec);
    else if(ft_strcmp(exec->tmp->args[0], "echo") == 0)
        ft_echo(exec);
    else if (ft_strcmp(exec->tmp->args[0], "env") == 0)
        ft_env(exec);
    else if(ft_strcmp(exec->tmp->args[0], "export") == 0)
        ft_export(exec);
    else if(ft_strcmp(exec->tmp->args[0], "unset") == 0)
        ft_unset(exec);
	else if (ft_strcmp(exec->tmp->args[0], "cd") == 0)
        ft_cd(exec);
    else
    {
        printf("minishell: %s: command not found\n", exec->tmp->args[0]);
        exec->status = 127;
    }
}

int	is_builtins(t_exec *exec)
{
    if(ft_strcmp(exec->tmp->args[0], "pwd") == 0)
        return (0);
    else if(ft_strcmp(exec->tmp->args[0], "exit") == 0)
        return (0);
    else if(ft_strcmp(exec->tmp->args[0], "echo") == 0)
        return (0);
    else if (ft_strcmp(exec->tmp->args[0], "env") == 0)
        return (0);
	else if (ft_strcmp(exec->tmp->args[0], "cd") == 0)
        return (0);
    else if (ft_strcmp(exec->tmp->args[0], "export") == 0)
        return 0;
    else if (ft_strcmp(exec->tmp->args[0], "unset") == 0)
        return 0;
    return (1);
}
