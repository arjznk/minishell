#include "minishell.h"

int	redirections(t_exec *exec)
{
	if(redir_infile(exec) == 1 || redir_outfile(exec) == 1)
		return (1);
	return (0);
}

int		redir_outfile(t_exec *exec)
{
	if ((*exec->cmd)->outfile && (*exec->cmd)->append == 1)
	{
		if ((exec->redir_fd = open((*exec->cmd)->outfile,
					O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	else if ((*exec->cmd)->outfile && (*exec->cmd)->append == 0)
	{
		if ((exec->redir_fd = open((*exec->cmd)->outfile,
					O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	return (0);
}

int		redir_infile(t_exec *exec)
{
	if ((*exec->cmd)->infile && (*exec->cmd)->append == 0)
	{
		if ((exec->redir_fd = open((*exec->cmd)->infile, O_RDONLY)) == -1)
		{
			redir_error(exec);
			return (1);
		}
	}
	return (0);
}

int	found_outfile(t_exec *exec)
{
	if ((*exec->cmd)->outfile)
		return (0);
	return (1);
}

int	found_infile(t_exec *exec)
{
	if ((*exec->cmd)->infile)
		return (0);
	return (1);
}

void	redir_error(t_exec *exec)
{
	if ((*exec->cmd)->infile)
		printf("minishell: %s: %s\n", (*exec->cmd)->infile, strerror(errno));
	else if ((*exec->cmd)->outfile && (*exec->cmd)->append == 0)
		printf("minishell: %s: %s\n", (*exec->cmd)->outfile, strerror(errno));
	else if ((*exec->cmd)->outfile && (*exec->cmd)->append == 1)
		printf("minishell: %s: %s\n", (*exec->cmd)->outfile, strerror(errno));
	exec->status = 1;
}
