/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 20:17:05 by rijebbar          #+#    #+#             */
/*   Updated: 2026/08/02 20:17:07 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtins_exec(t_exec *exec)
{
	create_saved_files(exec);
	builtins_pipe(exec);
}

void	signal_exec(t_exec *exec)
{
	wait_children(exec);
	init_parent_signals();
}
