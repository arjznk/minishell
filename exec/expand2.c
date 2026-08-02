/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:19:29 by rijebbar          #+#    #+#             */
/*   Updated: 2026/08/02 20:36:02 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_var2(t_exec *exec, char *result)
{
	exec->value = ft_itoa(exec->status);
	exec->new_result = ft_strjoin(result, exec->value);
	free(result);
	free(exec->value);
}

void	expand_var3(t_exec *exec, char *result)
{
	exec->value = ft_itoa(exec->pid);
	exec->new_result = ft_strjoin(result, exec->value);
	free(result);
	free(exec->value);
}
