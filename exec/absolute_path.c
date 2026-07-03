#include "minishell.h"

int    absolute_path(t_exec *exec)
{
    if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        return 0;
    return 1;
}

void    is_absolute_path(t_exec *exec)
{
    char *line;

    line = ft_strchr_echo((*exec->cmd)->args[0], 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(exec);
    else if(ft_strcmp(line, "pwd") == 0)
        ft_pwd();
    else if(ft_strcmp(line, "echo") == 0)
        ft_echo(exec);
    else if(ft_strcmp(line, "env") == 0)
        ft_env(exec);
    else if(ft_strcmp(line, "export") == 0 || ft_strcmp(line, "unset") == 0 || ft_strcmp(line, "exit") == 0)
    {
        printf("minishell: %s: No such file or directory\n", (*exec->cmd)->args[0]);
        exec->status = 127;
    }
    else
        redir_pipe_absolute(exec);
}

void    redir_pipe_absolute(t_exec *exec)
{
	char *valid_cmd;
    
    valid_cmd = exec->tmp->args[0];
    *exec->cmd = exec->tmp;
    if(fork() == 0)
    {
        if(access(valid_cmd, F_OK) != 0)
        {
            (dup2(exec->old_fd, STDIN_FILENO));
            cmd_error(exec);
        }
        if(exec->old_fd != -1)
            dup2(exec->old_fd, STDIN_FILENO);
        if(exec->tmp->next_cmd)
            dup2(exec->fd[1], STDOUT_FILENO);
        close_files(exec->fd);
        if(access(valid_cmd, F_OK) == 0)
            execve(valid_cmd, exec->tmp->args, exec->envp);
        else
            cmd_error(exec);
    }
}

void    exec_absolute_path(t_exec *exec)
{
    exec->saved_stdout = dup(STDOUT_FILENO);
    if(exec->tmp->next_cmd)
        dup2(exec->fd[1], STDOUT_FILENO);
    is_absolute_path(exec);
    dup2(exec->saved_stdout, STDOUT_FILENO);
    close(exec->saved_stdout); 
}