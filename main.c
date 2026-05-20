
#include "minishell.h"

void	print_list(t_env **env)
{
    // printf("a\n");
	t_env	*tmp;
    // printf("b\n");

	tmp = *env;
    // printf("c\n");
	if (!tmp)
		return ;
    // printf("d\n");
	while (tmp != NULL)
	{
        // printf("blabla\n");
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
    // printf("e\n");
}

void    get_path(char **envp, t_path *path)
{
    int i = 0;
    char *compar = "PATH=";
    
    while(ft_strncmp(compar, envp[i], 4) != 0)
        i++;
    path->path = envp[i];
    printf("%s\n", path->path);
}

int main(int ac, char **av, char **envp)
{
    t_env   *env;
    int     size;
    t_path *path;

    (void)av;
    (void)ac;
    path = NULL;
    env = NULL;
    size = 0;
    while (envp[size])
        size++;
    // printf("1\n");
    fill_list_env(envp, &env, size);
    // printf("2\n");
    // get_path(envp, path);
    // assign_name(&env);
    // printf("3\n");
    print_list(&env);
    // printf("4\n");
}

// recup et stock l'env -> moi
// areej -> tokenisation
// une fois env stock -> relier avec les commandes pour l'exec
