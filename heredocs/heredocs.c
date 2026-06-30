#include "minishell.h"

void    heredocs(t_exec *exec)
{
    char *line;
    if((*exec->cmd)->heredoc)
    {
        while(1)
        {
            line = readline(">");
            if(line)
                add_history(line);
            else
                continue;
            if(ft_strcmp(line, (*exec->cmd)->heredoc) == 0)
            {
                if((*exec->cmd)->next_cmd)
                    dup2(exec->fd[1], STDOUT_FILENO);
                else if(exec->fd[0] != -1)
                    dup2(exec->fd[0], STDIN_FILENO);
                free(line);
                break;
            }
            else
            {
                write(exec->fd[1], line, ft_strlen(line));
                write(exec->fd[1], "\n", 1);
            }
        }
        close(exec->fd[1]);
    }
}

int found_heredocs(t_exec *exec)
{
    if((*exec->cmd)->heredoc)
        return (0);
    return (1);
}
