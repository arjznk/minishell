#include "minishell.h"

void    execute_builtins(t_exec *exec)
{
    if(ft_strcmp((*exec->cmd)->args[0], "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp((*exec->cmd)->args[0], "exit") == 0)
        ft_exit(exec);
    else if(ft_strcmp((*exec->cmd)->args[0], "echo") == 0)
        ft_echo(exec);
    else if (ft_strcmp((*exec->cmd)->args[0], "env") == 0)
        ft_env(exec);
    else if(ft_strcmp((*exec->cmd)->args[0], "export") == 0)
        ft_export(exec);
    else if(ft_strcmp((*exec->cmd)->args[0], "unset") == 0)
        ft_unset(exec);
	else if (ft_strcmp((*exec->cmd)->args[0], "cd") == 0)
        ft_cd(exec);
    else if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        cmd_absolute_path(exec);
    else
    {
        printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
        exec->status = 127;
    }
}

int   is_builtins(t_exec *exec)
{
    if(ft_strcmp((*exec->cmd)->args[0], "pwd") == 0)
        return (0);
    else if(ft_strcmp((*exec->cmd)->args[0], "exit") == 0)
        return (0);
    else if(ft_strcmp((*exec->cmd)->args[0], "echo") == 0)
        return (0);
    else if (ft_strcmp((*exec->cmd)->args[0], "env") == 0)
        return (0);
	else if (ft_strcmp((*exec->cmd)->args[0], "cd") == 0)
        return (0);
    else if (ft_strcmp((*exec->cmd)->args[0], "export") == 0)
        return 0;
    else if (ft_strcmp((*exec->cmd)->args[0], "unset") == 0)
        return 0;
    else if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        return (0);
    return (1);
}

void    cmd_absolute_path(t_exec *exec)
{
    char *line;
    
    line = ft_strchr_echo(exec->line, 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(exec);
    else if(ft_strcmp(line, "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(line, "echo") == 0)
        ft_echo(exec);
    else if(ft_strcmp(line, "env") == 0)
        ft_env(exec);
    else if(ft_strcmp(line, "export") == 0 || ft_strcmp(line, "unset") == 0)
    {
        printf("minishell: %s: No such file or directory\n", (*exec->cmd)->args[0]);
        exec->status = 127;
    }
    else
        exec_pipe(exec);
}
