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

t_cmd   *parse_cmd(t_token *tokens)
{
    t_token   *tmp;
    t_cmd *new;
    t_cmd   *cmds;
    t_cmd   *current;

    tmp = tokens;
    cmds = NULL;
    new = new_cmd();
    add_cmd(&cmds, new);
    current = new;
    while (tmp)
    {
        if (tmp->type == T_PIPE)
        {
            new = new_cmd();
            add_cmd(&cmds, new);
            current = new;
        }
        tmp = tmp->next_token;
    }
    return(cmds);
}

void   add_args(t_cmd *current, char *str)
{
    char    **args;
    int i;

    i = 0;

    if (current->args)
    {
        while (current->args[i])
            i++;
    }
    args = malloc(sizeof(char *) * (i + 2));
}
