#include "minishell.h"

void	ft_echo(t_exec *exec)
{
	char	*cmd1;

    cmd1 = exec->tmp->args[0];
    if(cmd1 && exec->tmp->args[1] ==  NULL)
    {
        printf("\n");
        return;
    }
    if(check_n_valid(exec->tmp->args[1]) == 1)
    {
        echo_n(exec);
        return;
    }
    if(ft_strcmp(exec->tmp->args[1], "$?") == 0)
        exit_code(exec);
    else if(ft_strncmp(exec->tmp->args[1], "$", 1) == 0)
        printf("%s\n", exec->tmp->args[1]);
    else if(ft_strcmp(cmd1, "echo") == 0)
        echo(exec);
	else
	{
		printf("minishell: %s: command not found\n", cmd1);
		exec->status = 127;
	}
	exec->status = 0;
}

void	echo(t_exec *exec)
{
	char	**line;
	int		i;

    i = 1;
    line = exec->tmp->args;
    if(ft_strcmp(exec->tmp->args[0], "echo") == 0 && ft_strcmp(exec->tmp->args[1], "-n") == 0)
        return;
    while(line[i])
    {
        write(STDOUT_FILENO, line[i], ft_strlen(line[i]));
        if(line[i + 1])
            write(STDOUT_FILENO, " ", 1);
        i++;
    }
    write(STDOUT_FILENO, "\n", 1);
}

void	echo_n(t_exec *exec)
{
	int		i;
	char	**line;

    i = 1;
    line = exec->tmp->args;
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

int	check_n_valid(char *line)
{
	int	i;

	i = 0;
	if (line[0] != '-')
		return (0);
	else
	{
		i = 1;
		while (line[i])
		{
			if (line[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}
