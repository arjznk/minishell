#include "minishell.h"

void    ft_export(char *str, t_env **env)
{
    char *line;
    t_env *newnode;
    // char *variable;
    char *cmd;

    // printf("1\n");
    line = ft_strchr(str, ' ');
    // variable = search_and_stop(line, '=');
    // printf("2\n");
    char **all = ft_split(str, ' ');
    cmd = search_and_stop(str, ' ');
    newnode = malloc(sizeof(t_env));
    if(!newnode)
        return;
    if(ft_strcmp(cmd, "export") == 0)
    {
        if(!line)
        {
            export_only(env);
            return;
        }
        // printf("3\n");
        // else if(ft_strchr(variable, ' ') != NULL)
        // {
        //     printf("minishell: export: `=': not a valid identifier\n");
        //     return;
        // }
        else 
            export_w_error(all, env, newnode);
    }
}

void    export_w_error(char **all, t_env **env, t_env *newnode)
{
    int i = 1;
    while(all[i])
    {
        printf("all = %s\n", all[i]);
        newnode->variable = search_and_stop(all[i], ' ');
        newnode->value = ft_strchr(all[i], '=');
        i++;
    }
    ft_lstadd_back(env, newnode);
}

void    export_only(t_env **env)
{
	t_env *tmp;
	
    sort_str(env);
    tmp = *env;
    while(tmp)
    {
        if(tmp->value == NULL)
            printf("export %s=\"\"\n", tmp->variable);
        else
            printf("export %s=\"%s\"\n", tmp->variable, tmp->value);

		tmp = tmp->next;
    }
}
 
