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
    cmd->next = NULL;
    return(cmd);
}

