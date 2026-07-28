#include "minishell.h"

void	heredocs(t_exec *exec)
{
    int i;

    i = 0;
    pipe(exec->heredoc_fd);
    while(i < exec->tmp->nb_heredoc)
    {
        loop_heredoc(exec, i);
        i++;
    }
    close(exec->heredoc_fd[1]);
    exec->heredoc_fd[1] = -1;
}

void    loop_heredoc(t_exec *exec, int i)
{
    char *line;

    while(1)
    {
        line = readline(">");
        if(!line)
        {
            free(line);
            printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", 
                exec->count_line, exec->tmp->heredocs_delims[i]);
            break;
        }
        if( ft_strcmp(line, exec->tmp->heredocs_delims[i]) == 0)
        {
            free(line);
            break;
        }
        if(i == (exec->tmp->nb_heredoc - 1))
            heredoc_write(exec, line);
        else
            free(line);
    }
}

void    heredoc_write(t_exec *exec, char *line)
{
    write(exec->heredoc_fd[1], line, ft_strlen(line));
    write(exec->heredoc_fd[1], "\n", 1);
    free(line);
}

int	found_heredocs(t_exec *exec)
{
    if(exec->tmp->heredoc)
        return (0);
    return (1);
}

void	close_heredoc_files(t_exec *exec)
{
	close(exec->heredoc_fd[0]);
}
