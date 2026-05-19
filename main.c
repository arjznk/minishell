
#include "minishell.h"

// void	print_list(t_env **env)
// {
// 	t_env	*tmp;

// 	tmp = *env;
// 	if (!tmp)
// 		return ;
// 	while (tmp != NULL)
// 	{
// 		printf("%s\n", tmp->value);
// 		tmp = tmp->next;
// 	}
// }

// void    get_path(char **envp, t_path *path)
// {
//     int i = 0;
//     char *compar = "PATH=";
    

//     while(ft_strncmp(compar, envp[i], 5) != 0)
//         i++;
//     path->path = envp[i];
//     // printf("%s\n", path->path);
// }

// int main(int ac, char **av, char **envp)
// {

//     t_env   *env;
//     int     size;
//     t_path *path;

//     (void)av;
//     (void)ac;
//     path = NULL;
//     env = NULL;
//     size = 0;
//     while (envp[size])
//         size++;
//     fill_list_env(envp, &env, size);
//     // get_path(envp, path);
//     print_list(&env);
// }


int main (int ac, char **av)
{
    if (ac > 1)
    {
        int i = 1;
        while (av[i])
        {
            token_type(av[i]);
            i++;
        }
        printf("%s\n", find_word(av[1]));
    }
    return 0;
}

// int main(void)
// {
//     t_token *new;

//     new = new_token("echo", T_WORD);
//     printf("%s\n", new->str);
//     printf("%d\n", new->type);
//     printf("%p\n", new->next_token);
//     return (0);
// }
