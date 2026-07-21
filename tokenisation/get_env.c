#include "minishell.h"

void fill_list_env(char **envp, t_env **env, int size, t_exec *exec)
{
    int i;
    t_env *newnode;
    
    i= 0;
    if(!envp)
        return;
    while(i < size)
    {
        newnode = ft_lstnew_for_env(envp[i], exec);
        ft_lstadd_back(env, newnode);
        i++;
    }
}

void	get_and_cut_path(char **envp, t_path *path)
{
    int i = 0;
    char *compar = "PATH";
  
    if(!envp[i])
        return;
    while(envp[i] != NULL && ft_strncmp(compar, envp[i], 4) != 0 )
        i++;
    path->path_env = envp[i];
    path->path_acces = ft_split(path->path_env, ':');
}

void    fill_path_acces(t_path_acces **acces, t_exec *exec)
{
    int i;
    t_path_acces *newnode;

    i = 0;
    if(!exec->path->path_acces)
        return;
    while(exec->path->path_acces[i])
    {
        newnode = ft_lstnew_for_path(exec->path->path_acces[i]);
        ft_lstadd_back_path(acces, newnode);
        i++;
    }
}

void	add_to_env(t_exec *exec, t_env *newnode, int i)
{
    newnode = ft_lstnew_for_env((*exec->cmd)->args[i], exec);
    ft_lstadd_back((exec->env), newnode);
}

void	path_function(t_exec *exec, int size)
{
    fill_list_env(exec->envp, exec->env, size, exec);
    get_and_cut_path(exec->envp, exec->path);
    fill_path_acces(exec->acces_path, exec);
}
