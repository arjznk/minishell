
#include "minishell.h"

void    execute_builtins(char *line, t_env **env)
{
    ft_pwd(line);
    ft_exit(line);
    ft_echo(line);
    ft_env(line, env);
}

int main(int ac, char **av, char **envp)
{
    t_env   *env;
    int     size;
    t_path *path;

    (void)av;
    (void)ac;

    path = malloc(sizeof(t_path));
    env = malloc(sizeof(t_env));
    env = NULL;
    size = 0;
    while (envp[size])
        size++;
    fill_list_env(envp, &env, size);
    get_and_cut_path(envp, path);
    get_only_access(path);
    char *line;
    while(1)
    {
        line = readline("minishell>");
        if(line)
            add_history(line);
        execute_builtins(line, &env);
        
    }
}

// lire et stock ce que j'ecris dans le term
// ensuite interpreter 
// grace au parsing ? si mot alors -> mot et si commande alors -> cmd
// et si cmd alors exec avec le chemin absolu /usr/bin
// faire les builtin : echo (avec -n, donc on affiche pas le retour a la ligne)
// cd avec -> opendir, readdir, closedir, chdir
// pour tout les builtin utiliser getenv -> prendre la valeur de l'env
// export ->
// unset (supprimer une variable)  
//env -> affiche l'env 
//exit -> exit le bash 

// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec
