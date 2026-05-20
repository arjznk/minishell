
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

    while(1)
    {
        readline("minishell>");
    }
    // print_list(&env);
}

// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec
