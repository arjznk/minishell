 
#include "minishell.h"

void    execute_builtins(char *line, t_env **env)
{
    if(ft_strncmp(line, "pwd", 3) == 0)
        ft_pwd();
    else if(ft_strncmp(line, "exit", 4) == 0)
        ft_exit(line);
    if(ft_strncmp(line, "echo", 4) == 0)
        ft_echo(line);
    else if (ft_strncmp(line, "env", 3) == 0)
        ft_env(line, env);
    else if(ft_strncmp(line, "export", 6) == 0)
        ft_export(line, env);
    if(ft_strncmp(line, "unset", 5) == 0)
        ft_unset(line, env);
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

// et si cmd alors exec avec le chemin absolu /usr/bin
// faire les builtin : 
// cd avec -> opendir, readdir, closedir, chdir
// pour tout les builtin utiliser getenv -> prendre la valeur de l'env


// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec
