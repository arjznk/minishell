#include "minishell.h"

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

int	check_directory(t_exec *exec)
{
    struct stat st;

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
            return(1);
        }
    }
    return(0);
}
