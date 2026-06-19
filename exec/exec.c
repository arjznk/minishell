#include "minishell.h"

void    exec_pipe(t_exec *exec)
{
    int temp;
    int status;

    temp = -1;
    status = -1;
    while((*exec->cmd))
    {
        int fd[2];
        pipe(fd);
        if(fork() == 0)
        {
            if(ft_strncmp(exec->line, "/usr/bin/", 9) == 0)
            redir_pipe_absolute(exec, fd, temp);
            else
            redir_pipe(exec, fd, temp);
        }
        temp = fd[0];
        close(fd[1]);
        (*exec->cmd) =(*exec->cmd)->next_cmd; 
    }
    while(waitpid(-1, &status, 0) > 0)
        exec->status = WEXITSTATUS(status);
}

void    redir_pipe(t_exec *exec, int fd[2], int temp)
{
    char *newline;
    char *preline;
    char *valid_cmd;
    
    newline = ft_strjoin(exec->path->access_usr, "/");
    preline = (*exec->cmd)->args[0];
    valid_cmd = ft_strjoin(newline, preline);
    if(temp != -1)
        (dup2(temp, STDIN_FILENO));
    if((*exec->cmd)->next_cmd)
        (dup2(fd[1], STDOUT_FILENO));
    close(fd[0]);
    close(fd[1]);
    if(is_builtins(exec) == 0)
    {
        execute_builtins(exec);
        exec->status = 0;
    }
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, (*exec->cmd)->args, exec->envp);
    else
    {
        printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
        exec->status = 127;
    }
}

void    redir_pipe_absolute(t_exec *exec, int fd[2], int temp)
{
	char *valid_cmd;
    
    valid_cmd = (*exec->cmd)->args[0];
    if(temp != -1)
        dup2(temp, STDIN_FILENO);
    if((*exec->cmd)->next_cmd)
        dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    if(is_builtins(exec) == 0)
    {
        execute_builtins(exec);
        exec->status = 0;
    }
    if(access(valid_cmd, F_OK) == 0)
        execve(valid_cmd, (*exec->cmd)->args, exec->envp);
    else
    {
        printf("minishell: %s: command not found\n", (*exec->cmd)->args[0]);
        exec->status = 127;
    }
}

/*
faire les heredoc a part de l'exec, et localiser le heredoc dans une commande 
et l'executer avant d'executer le reste
*/

