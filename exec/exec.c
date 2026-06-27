#include "minishell.h"

void    exec_pipe(t_exec *exec)
{
    int temp;
    int status;

    t_cmd *tmp;
    temp = -1;
    status = -1;
    tmp = (*exec->cmd);
    while(tmp)
    {
        int fd[2];
        pipe(fd);
        if(found_heredocs(exec) == 1)
            heredocs(exec);
        if(fork() == 0)
        {
            if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
                redir_pipe_absolute(exec, fd, temp, tmp);
            else
                redir_pipe(exec, fd, temp, tmp);
        }
        temp = fd[0];
        close(fd[1]);
        tmp = tmp->next_cmd; 
    }
    while(waitpid(-1, &status, 0) > 0)
        exec->status = WEXITSTATUS(status);
}

void    redir_pipe(t_exec *exec, int fd[2], int temp, t_cmd *tmp)
{
    char *newline;
    char *valid_cmd;
    
    newline = ft_strjoin(exec->path->access_usr, "/");
    valid_cmd = ft_strjoin(newline, tmp->args[0]);
    *exec->cmd = tmp;
    if(access(valid_cmd, F_OK) != 0)
    {
        (dup2(temp, STDIN_FILENO));
        cmd_error(exec);
    }
    if(temp != -1)
        (dup2(temp, STDIN_FILENO));
    if(tmp->next_cmd)
        (dup2(fd[1], STDOUT_FILENO));
    close_files(fd);
    if(is_builtins(exec) == 0)
    {
        execute_builtins(exec);
        exit(exec->status);
    }
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, tmp->args, exec->envp);
    else
        cmd_error(exec);
}

void    redir_pipe_absolute(t_exec *exec, int fd[2], int temp, t_cmd *tmp)
{
	char *valid_cmd;
    
    valid_cmd = tmp->args[0];
    *exec->cmd = tmp;
    if(access(valid_cmd, F_OK) != 0)
    {
        (dup2(temp, STDIN_FILENO));
        cmd_error(exec);
    }
    if(temp != -1)
        dup2(temp, STDIN_FILENO);
    if(tmp->next_cmd)
        dup2(fd[1], STDOUT_FILENO);
    close_files(fd);
    if(is_builtins(exec) == 0)
    {
        execute_builtins(exec);
        exit(exec->status);
    }
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, tmp->args, exec->envp);
    else
        cmd_error(exec);
}

/*
faire les heredoc a part de l'exec, et localiser le heredoc dans une commande 
et l'executer avant d'executer le reste
*/

void    cmd_error(t_exec *exec)
{
    printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
    exec->status = 127;
    exit(127);
}

void    close_files(int fd[2])
{
    close(fd[0]);
    close(fd[1]);
}
