#include "minishell.h"

void    heredocs(t_exec *exec)
{
    char *line;
    if((*exec->cmd)->heredoc)
    {
        int fd[2];
        pipe(fd);
        while(1)
        {
            line = readline(">");
            if(line)
                add_history(line);
            else
                continue;
            if(ft_strcmp(line, (*exec->cmd)->heredoc) == 0)
            {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                close(fd[1]);
                break;
            }
            else
            {
                write(fd[1], line, ft_strlen(line));
                write(fd[1], "\n", 1);
            }
        }
        free(line);
    }
}

/*
quand plusieurs pipes si pas la derniere, entrer dans le heredoc
rediriger la sortie vers la pipe suivante 
parent execute heredoc 
*/

int found_heredocs(t_exec *exec)
{
    if((*exec->cmd)->heredoc)
        return (1);
    return (0);
}
