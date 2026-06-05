#include "minishell.h"

void	print_list(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->variable);
		tmp = tmp->next;
	}
}

char *search_and_stop(char *str, char c)
{
    int i;
    char *dest;
    
    i = 0;
    dest = malloc(sizeof(char) * ft_strlen(str));
    if(!dest)
        return NULL;
    while(str[i] && str[i] != c)
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *str_between(char *str, char c)
{
    char *line;

    line = ft_strchr(str, c);
    line = search_and_stop(line, c);
    return(line);
}

int c_strcmp(char *str, char b)
{
    int i;
    
    i = 0;
    while(str[i])
    {
        if(str[i] == b)
            return (0);
        i++;
    }
    return (1);
}

// void    sort_str(t_env **env)
// {
//     t_env *tmp;

//     tmp = *env;
//     while()
//     {
//         while(tmp )
//         {
//             if(ft_strcmp(tmp->variable, tmp->next->variable) > 0)
//             {
//                 // donc s1 > s2 donc swap value et variable
//             }
//         }
//     }
// }
/*
boucle tant que tout n'est pas trie
2e boucle, on compare tmp avc tmp->next
si tmp->variable > tmp->next->variable on swap + value aussi*/
