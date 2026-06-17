#include "minishell.h"

void    ft_echo(t_exec *exec)
{
    char *cmd;

    cmd = (*exec->cmd)->args[0];
    if(ft_strncmp(cmd, "echo -n", 7) == 0)
    {
        echo_n(exec);
        return;
    }
    if(ft_strcmp(cmd, "echo") == 0)
    {
        // if(ft_strcmp(str, "$") == 0)
        //     echo_variable(env, str);
            echo_quote(exec);
    }
    else
        printf("minishell: %s: command not found\n", cmd);
}

void    echo_quote(t_exec *exec)
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
    line = (*exec->cmd)->args[1];
    while(line[i])
    {
        while(line[i] == '\'' || line[i] == (char)'"')
            i++;
        write(1, &line[i++], 1);
    }
}

void    echo_variable(t_env **env, char *str)
{
    char *line;

    line = ft_strchr_echo(str, ' ');
    if(ft_strcmp(line, (*env)->variable) == 0)
        printf("%s\n", (*env)->variable);
}
