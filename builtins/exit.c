#include "minishell.h"

void	ft_exit(t_exec *exec)
{
	char	*nb;
	char	*cmd;

    nb = exec->tmp->args[1];
    cmd = exec->tmp->args[0];
    if(ft_strcmp(cmd, "exit") == 0)
    {
        if(cmd && !nb)
        {
			printf("exit\n");
            exit_return(exec);
			for (int fd = 0; fd < 10; fd++)
			{
    			if (fcntl(fd, F_GETFD) != -1)
        		printf("FD %d est ouvert\n", fd);
			}
            exit(0);
        }
        else if(cmd && ft_isdigit(nb) == 1)
        {
            printf("exit\nminishell: exit: %s: numeric argument required\n", nb);
            exit_return(exec);
            exit(2);
        }
        else
            ft_exit_code(cmd, nb, exec);
    }
    else
        printf("minishell: %s: command not found\n", cmd);
}

void	ft_exit_code(char *line, char *nb, t_exec *exec)
{
	long	nbr;

	if ((line && ft_isdigit(nb) == 0))
	{
		nbr = ft_atoi(nb);
		if (nbr > INT_MAX || nbr < INT_MIN)
		{
			printf("exit\nminishell: exit: %ld: numeric argument required\n",
				nbr);
			exit_return(exec);
			exit(2);
		}
		if (nbr > 255)
		{
			printf("exit\n");
			exit_return(exec);
			exit(nbr % 256);
		}
		else
		{
			printf("exit\n");
			exit_return(exec);
			exit(nbr);
		}
	}
}

void	exit_return(t_exec *exec)
{
	close_files(exec);
	close_saved_files(exec);
	free_all(exec);
}
