#include "minishell.h"

void    ft_export(char *str, t_env **env)
{
    char *line;
    t_env *newnode;
    char *variable;
    char *value;

    line = ft_strchr(str, ' ');
    if(!line)
    {
		export_only(env);
		return;
	}
    variable = search_and_stop(line, '=');
    value = ft_strchr(line, '=');
    newnode = malloc(sizeof(t_env));
    if(!newnode)
        return;
    if(ft_strchr(variable, ' ') != NULL)
    {
        printf("minishell: export: `=': not a valid identifier\n");
        return;
    }
    else if(ft_strncmp(value, " ", 1) == 0)
        export_space(variable, newnode, env);
    else
        export_w_error(line, env, newnode);
}

void    export_space(char *variable, t_env *newnode, t_env **env)
{
    newnode->variable = variable;
    newnode->value = " ";
    ft_lstadd_back(env, newnode);
}

void    export_w_error(char *line, t_env **env, t_env *newnode)
{
    newnode->variable = search_and_stop(line, '=');
    newnode->value = ft_strchr(line, '=');
    ft_lstadd_back(env, newnode);
}
void    export_only(t_env **env)
{
	t_env *tmp;
	
    sort_str(env);
    tmp = *env;
    while(tmp)
    {
        printf("export %s=\"%s\"\n", tmp->variable, tmp->value);
		tmp = tmp->next;
    }
}





/*
si export seul : 
declare -x devant chaque ligne 
les lignes s'affichent par ordre alpha
chaque value est entre ""
ex : 
declare -x USERNAME="rijebbar"

faire un sort, pour trier

*/