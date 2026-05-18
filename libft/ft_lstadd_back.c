/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:51:20 by rijebbar          #+#    #+#             */
/*   Updated: 2026/05/18 10:59:52 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*newnode;

	newnode = *lst;
	if (newnode == NULL)
	{
		*lst = new;
		return ;
	}
	while (newnode->next != NULL)
		newnode = newnode->next;
	newnode->next = new;
}
