#include "minishell.h"

void fill_list_env(char **envp, t_env **env, int size)
{
    int i = 0;
    t_env *newnode;
    while(i < size)
    {
        newnode = ft_lstnew_for_env(envp[i]);
        ft_lstadd_back(env, newnode);
        i++;
    }
}

void    get_and_cut_path(char **envp, t_path *path)
{
    int i = 0;
    char *compar = "PATH";
  
    while(envp[i] != NULL && ft_strncmp(compar, envp[i], 4) != 0 )
        i++;
    path->path_env = envp[i];
    path->path_access = ft_split(path->path_env, ':');
}

void    get_only_access(t_path *path)
{
    int i = 0;
    char *compar = "/usr/bin";

    while(path->path_access[i] && ft_strncmp(compar, path->path_access[i], 8) != 0)
        i++;
    path->access_usr = path->path_access[i];
}

void    add_to_env(t_exec *exec, t_env *newnode, int i)
{
    newnode = ft_lstnew_for_env((*exec->cmd)->args[i]);
    ft_lstadd_back((exec->env), newnode);
}
