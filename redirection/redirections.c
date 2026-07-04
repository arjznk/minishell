#include "minishell.h"

void    redirections(t_exec *exec)
{
    char *valid_cmd;

    valid_cmd = exec->tmp->args[0];
    int fd;

    if((fd = open((*exec->cmd)->outfile, O_CREAT | O_WRONLY | T_APPEND, 0644)) != -1)
    {
        if(access(valid_cmd, F_OK) == 0)
            dup2(fd, STDOUT_FILENO);
        if(fork() == 0)
        {
            if(access(valid_cmd, F_OK) == 0)
                execve(valid_cmd, exec->tmp->args, exec->envp);
            else
                cmd_error(exec);
        }

    }   
    else
    {
        perror((*exec->cmd)->outfile);
        exec->status = 127;
        return;
    }
}

int     found_redir(t_exec *exec)
{
    if((*exec->cmd)->outfile)
        return (0);
    return(1);
}
