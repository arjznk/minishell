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
                break;
            if(ft_strcmp(line, (*exec->cmd)->heredoc) == 0)
            {
                free(line);
                break;
            }
            write(exec->heredoc_fd[1], line, ft_strlen(line));
            write(exec->heredoc_fd[1], "\n", 1);
            free(line);
        }
        close(exec->heredoc_fd[1]);
    }
}

int found_heredocs(t_exec *exec)
{
    if((*exec->cmd)->heredoc)
        return (0);
    return (1);
}
