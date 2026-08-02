/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 15:48:50 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 20:57:07 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_exec *exec)
{
	char	*nb;
	char	*cmd;

	nb = exec->tmp->args[1];
	cmd = exec->tmp->args[0];
	if (ft_strcmp(cmd, "exit") != 0)
	{
		printf("minishell: %s: command not found\n", cmd);
		return ;
	}
	if (!nb)
		return (printf("exit\n"), exit_return(exec), exit(0));
	if (exec->tmp->args[2])
	{
		printf("exit\nminishell: exit: too many arguments\n");
		return (exit_return(exec), exit(2));
	}
	if (!is_valid_number(nb))
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n", nb);
		return (exit_return(exec), exit(2));
	}
	ft_exit_code(nb, exec);
}

int	is_valid_number(char *nb)
{
	int	i;

	i = 0;
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	if (!nb[i])
		return (0);
	while (nb[i])
	{
		if (ft_isdigit(nb[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit_code(char *nb, t_exec *exec)
{
	long long	nbr;
	int			sign;
	int			i;
	int			digit;

	nbr = 0;
	sign = 1;
	i = 0;
	if (nb[i] == '+' || nb[i] == '-')
	{
		if (nb[i] == '-')
			sign = -1;
		i++;
	}
	while (nb[i])
	{
		digit = nb[i] - '0';
		if (nbr > (LLONG_MAX - digit) / 10)
			return (printf("exit\nminishell: exit: \
					%s: numeric argument required\n", nb), exit_return(exec),
				exit(2));
		nbr = nbr * 10 + digit;
		i++;
	}
	nbr *= sign;
	return (printf("exit\n"), exit_return(exec), exit((unsigned char)nbr));
}

void	exit_return(t_exec *exec)
{
	close_files(exec);
	close_saved_files(exec);
	free_all(exec);
}
