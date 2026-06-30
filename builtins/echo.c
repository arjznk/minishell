#include "minishell.h"

void    ft_echo(t_exec *exec)
{
    char *cmd1;
    int i;

    i = 1;

    if(ft_strncmp((*exec->cmd)->args[0], "/usr/bin/", 9) == 0)
        cmd1 = ft_strchr_echo((*exec->cmd)->args[0], 'n');
    else
        cmd1 = (*exec->cmd)->args[0];
    if(cmd1 && (*exec->cmd)->args[1] ==  NULL)
    {
        printf("\n");
        return;
    }
    if(check_n_valid((*exec->cmd)->args[1]) == 1)
        echo_n(exec);
    if(ft_strcmp((*exec->cmd)->args[1], "$?") == 0)
        exit_code(exec);
    else if(ft_strncmp((*exec->cmd)->args[1], "$", 1) == 0)
        printf("%s\n", (*exec->cmd)->args[i]);
    else if(ft_strcmp(cmd1, "echo") == 0)
        echo(exec);
	else
	{
		printf("minishell: %s: command not found\n", cmd1);
		exec->status = 127;
	}
		exec->status = 0;
}

void    echo(t_exec *exec)
{
    char **line;
    int i;

    i = 1;
    line = (*exec->cmd)->args;
    while(line[i])
    {

        printf("%s", line[i]);
        if(line[i + 1])
            printf(" ");
        i++;
    }
    printf("\n");
}

void   echo_n(t_exec *exec)
{
    int i;
    char **line;

    i = 1;
    line = (*exec->cmd)->args;
    while(line[i])
    {
        if(check_n_valid(line[i]) == 1)
            i++;
        else
        {
            printf("%s", line[i]);
            if(line[i + 1])
                printf(" ");
            i++;
        }
    }
}

int check_n_valid(char *line)
{
    int i;
    
    i= 0;
    if(line[0] != '-')
        return (0);
    else
    {
        i = 1;
        while(line[i])
        {
            if(line[i] != 'n')
                return (0);
            i++;
        }
    }
    return(1);
}
