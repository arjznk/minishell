#include "minishell.h"

void    execute_builtins(t_exec *exec)
{
    if(ft_strcmp(exec->line, "pwd") == 0)
        ft_pwd();
    else if(ft_strncmp(exec->line, "exit", 4) == 0)
        ft_exit(exec->line);
    else if(ft_strncmp(exec->line, "echo", 4) == 0)
        ft_echo(exec->line, exec->env);
    else if (ft_strcmp(exec->line, "env") == 0)
        ft_env(exec->line, exec->env);
    else if(ft_strncmp(exec->line, "export", 6) == 0)
        ft_export(exec->line, exec->env);
    else if(ft_strncmp(exec->line, "unset", 5) == 0)
        ft_unset(exec->line, exec->env);
	else if (ft_strncmp(exec->line, "cd", 2) == 0)
        ft_cd(exec->line);
    else if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
        cmd_absolute_path(exec);
	else
        exec_pipe(exec);
}

void    cmd_absolute_path(t_exec *exec)
{
    char *line;
    
    line = ft_strchr_echo(exec->line, 'n');
    if(ft_strncmp(line, "cd", 2) == 0)
        ft_cd(line);
    else if(ft_strncmp(line, "pwd", 3) == 0)
        ft_pwd();
    else if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(line, exec->env);
    else if(ft_strncmp(line, "cd", 2) == 0)
        return;
    else if(ft_strncmp(line, "env", 3) == 0)
        ft_env(line, exec->env);
    else
        exec_pipe(exec);

}

void    exec_pipe(t_exec *exec)
{
    t_cmd *tmp;
    int temp;

    tmp = (*exec->cmd);
    temp = -1;
    while(tmp)
    {
        int fd[2];
        pipe(fd);
        if(fork() == 0)
        {
            if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
                redir_pipe_absolute(exec, tmp, fd, temp);
            else
                redir_pipe(exec, tmp, fd, temp);
        }
        temp = fd[0];
        close(fd[1]);
        tmp = tmp->next_cmd;
    }
    while(waitpid(-1, NULL, 0) > 0)
    ;
}

void    redir_pipe(t_exec *exec, t_cmd *tmp, int fd[2], int temp)
{
    char *newline;
    char *preline;
    char *valid_cmd;
    
    int size = ft_lstsize((*exec->cmd));
    newline = ft_strjoin(exec->path->access_usr, "/");
    preline = tmp->args[0];
    valid_cmd = ft_strjoin(newline, preline);
    if(size >= 3)
    {
        if(temp != -1)
            dup2(temp, STDIN_FILENO);
        else if(tmp->next_cmd && temp == -1)
            dup2(fd[1], STDOUT_FILENO);
    }
    else
    {
        if(temp != -1)
            dup2(temp, STDIN_FILENO);
        else if(tmp->next_cmd && temp == -1)
            dup2(fd[1], STDOUT_FILENO);
    }
    close(fd[0]);
    close(fd[1]);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, tmp->args, exec->envp);
}

void    redir_pipe_absolute(t_exec *exec, t_cmd *tmp, int fd[2], int temp)
{
	char *valid_cmd;
    
    valid_cmd = tmp->args[0];
    if(temp != -1)
        dup2(temp, STDIN_FILENO);
    else if(tmp->next_cmd && temp == -1)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, tmp->args, exec->envp);
}

/*
fd[0] = lecture
fd[1] = ecriture
*/

