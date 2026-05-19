/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 16:40:35 by rijebbar          #+#    #+#             */
/*   Updated: 2026/05/19 12:29:16 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fill_list_env(char **envp, t_env **env, int size)
{
    int i = 0;
    t_env *newnode;
    while(i < size)
    {
        newnode = ft_lstnew(envp[i]);
        ft_lstadd_back(env, newnode);
        i++;
    }
}

// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec