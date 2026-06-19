#include "minishell.h"

void    ft_echo(t_exec *exec)
{
    char *cmd1;
    char *cmd2;
    char *tmp;
    char *final_cmd;

    cmd1 = (*exec->cmd)->args[0];
    tmp = " ";
    cmd2 =  ft_strjoin(cmd1, tmp);
    final_cmd =  ft_strjoin(cmd2, (*exec->cmd)->args[1]);
    if(ft_strncmp(final_cmd, "echo -n", 7) == 0)
        echo_n(exec);
    else if(ft_strcmp((*exec->cmd)->args[1], "$?") == 0)
        exit_code(exec);
    else if(ft_strncmp((*exec->cmd)->args[1], "$", 1) == 0)
        expand_var(exec);
    else if(ft_strcmp(cmd1, "echo") == 0)
        echo(exec);
    else
    {
        printf("minishell: %s: command not found\n", cmd1);
        exec->status = 127;
    }
}

void    echo(t_exec *exec)
{
    char *line;
    int i;

    i = 0;
    line = (*exec->cmd)->args[1];
    if(line == NULL)
    {
        printf("\n");
        return;
    }
    while(line[i])
    {
        while(line[i] == '\'' || line[i] == (char)'"')
            i++;
        write(1, &line[i++], 1);
    }
    printf("\n");
}

void   echo_n(t_exec *exec)
{
    char *line;
    int i;

    i = 0;
    line = (*exec->cmd)->args[2];
    while(line[i])
    {
        while(line[i] == '\'' || line[i] == (char)'"')
            i++;
        write(1, &line[i++], 1);
    }
}



