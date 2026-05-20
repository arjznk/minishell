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

// void    assign_name(t_env **env)
// {
//     while(*env != NULL)
//     {
//         (*env)->value = ft_strchr((*env)->variable, '=');
//         *env = (*env)->next;
//     }
// }

// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec