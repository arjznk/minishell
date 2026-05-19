/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:25:14 by rijebbar          #+#    #+#             */
/*   Updated: 2026/05/19 16:25:19 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void    get_path(char **envp, t_path *path)
{
    int i = 0;
    char *compar = "PATH=";
    

    while(ft_strncmp(compar, envp[i], 5) != 0)
        i++;
    path->path == envp[i];
}

int main(int ac, char **av, char **envp)
{
    t_env **env;
    (void)av;
    env = malloc(sizeof(t_env));
    fill_list_env(envp, env, ac-1);
    // print_list(env);

    while(1)
    {
        
    }
}

// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec
