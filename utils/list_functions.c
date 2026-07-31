/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 17:47:20 by azenk             #+#    #+#             */
/*   Updated: 2026/07/31 17:58:11 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_for_env(char *value, t_exec *exec)
{
	t_env	*lstnew;
	char	*tmp;

	lstnew = malloc(sizeof(t_env));
	if (!lstnew)
		return (NULL);
	if (ft_strchr(value, '=') != NULL)
	{
		tmp = ft_strchr(value, '=');
		lstnew->value = ft_strdup(tmp);
		lstnew->variable = search_and_stop(value, '=');
		if (ft_strcmp(lstnew->variable, "HOME") == 0)
			exec->home = lstnew->value;
		if (ft_strcmp(lstnew->variable, "OLDPWD") == 0)
			exec->old_pwd = ft_strdup(lstnew->value);
	}
	else
	{
		lstnew->variable = ft_strdup(value);
		lstnew->value = NULL;
	}
	lstnew->next = NULL;
	return (lstnew);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*newnode;

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

t_path_acces	*ft_lstnew_for_path(char *value)
{
	t_path_acces	*lstnew;

	lstnew = malloc(sizeof(t_env));
	if (!lstnew)
		return (NULL);
	lstnew->acces = ft_strdup(value);
	lstnew->next = NULL;
	return (lstnew);
}

void	ft_lstadd_back_path(t_path_acces **lst, t_path_acces *new)
{
	t_path_acces	*newnode;

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
