#include "minishell.h"

// int	dot_error_return(t_exec *exec, int i, char *cmd)
// {
// 	if (count_dots(exec->tmp->args[i]) == 2)
// 	{
// 		if (ft_strcmp("cd", exec->tmp->args[0]) == 0 && ft_strcmp("..",
// 				exec->tmp->args[1]) == 0)
// 			return (0);
// 		else
// 		{
// 			return_point(exec, cmd);
// 			return (1);
// 		}
// 	}
// 	else if (count_dots(exec->tmp->args[i]) > 1)
// 	{
// 		return_point(exec, cmd);
// 		return (1);
// 	}
// 	else if (ft_strcmp(cmd, ".") == 0)
// 	{
// 		return_point_only(exec, cmd);
// 		return (1);
// 	}
// 	else if (cmd[0] == '.' && (cmd[1] == '\0' || cmd[1] == '/'))
// 		return (return_point_slash(exec), 1);
// 	return (0);
// }

int	dot_error_return(t_exec *exec, int i, char *cmd)
{
	if (cmd[0] == '.' && cmd[1] == '/')
		return (return_point_slash(exec), 1);
	else if (ft_strcmp(cmd, "..") == 0)
	{
		if (ft_strcmp("cd", exec->tmp->args[0]) == 0)
			return (0);
		return_point(exec, cmd);
		return (1);
	}
	else if (count_dots(exec->tmp->args[i]) > 2)
	{
		return_point(exec, cmd);
		return (1);
	}
	else if (ft_strcmp(cmd, ".") == 0)
	{
		return_point_only(exec, cmd);
		return (1);
	}
	return (0);
}

void	return_point_slash(t_exec *exec)
{
	printf("minishell: %s : Is a directory\n", exec->tmp->args[0]);
	exec->status = 126;

}

void	return_point_only(t_exec *exec, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": filename argument required", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": usage: . [-p path] filename [arguments]", 2);
	exec->status = 2;
}

void	return_point(t_exec *exec, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	exec->status = 127;
}

int	count_dots(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '.')
			count++;
		i++;
	}
	return (count);
}
