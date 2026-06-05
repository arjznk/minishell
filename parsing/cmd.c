#include "../minishell.h"

t_cmd   *new_cmd (void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->args = NULL;
    cmd->append = 0;
    cmd->heredoc = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->next_cmd = NULL;
    return(cmd);
}

void    add_cmd(t_cmd **cmds, t_cmd *new)
{
    t_cmd *tmp;

    tmp = *cmds;
    if (!*cmds)
    {
        *cmds = new;
        return ;
    }
    else
    {
        while (tmp->next_cmd)
            tmp = tmp->next_cmd;
    }
    tmp->next_cmd = new;
}

