#include "minishell.h"

void    heredocs(t_exec *exec)
{
    char *line;
    int temp = -1;
    if((*exec->cmd)->heredoc)
    {
        int fd[2];
        pipe(fd);
        line = readline(">");
        if(ft_strcmp(line, (*exec->cmd)->args[1]) == 0)
        {
            printf("%s\n", line);
            exit(0);
        }
        else
        {
            if(temp != -1)
                (dup2(temp, STDIN_FILENO));
            (dup2(fd[1], STDOUT_FILENO));
        }
        temp = fd[0];
    }
}

int found_heredocs(t_exec *exec)
{
    if((*exec->cmd)->heredoc)
        return (1);
    return (0);
}
