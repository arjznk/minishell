#include "minishell.h"

void    heredocs(t_exec *exec)
{
    char *line;
    if((*exec->cmd)->heredoc)
    {
        pipe(exec->heredoc_fd);
        while(1)
        {
            line = readline(">");
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
    {
        printf("found\n");
        return (0);
    }
    return (1);
}

void    close_heredoc_files(t_exec *exec)
{
    close(exec->heredoc_fd[0]);
}
