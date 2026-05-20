
#include "minishell.h"

void	print_list(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next_token;
	}
}

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
    t_token *token;
    t_token *new;
    t_token_type *type;

    type = malloc(sizeof(t_token_type));
    token = malloc(sizeof(t_token));
    if (ac > 1)
    {
        int i = 1;
        while (av[i])
        {
            cmd_type(av[i]);
            new = new_token(av[i], T_WORD);
            i++;
        }
        printf("%s\n", find_word(av[1]));
        print_list(&new);
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
