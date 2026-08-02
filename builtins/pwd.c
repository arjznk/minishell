/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:49:25 by azenk             #+#    #+#             */
/*   Updated: 2026/08/02 20:06:45 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	buf[BUFFER_SIZE];

	if (getcwd(buf, BUFFER_SIZE) == NULL)
	{
		printf("minishell: pwd: %s\n", strerror(errno));
		return ;
	}
	printf("%s\n", buf);
}
