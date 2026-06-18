#include "minishell.h"

void    ft_export(t_exec *exec)
{
    t_env *newnode;
    char *cmd;

    cmd = (*exec->cmd)->args[0];;
    newnode = malloc(sizeof(t_env));
    if(!newnode)
		return ;
	if((*exec->cmd)->args[0] && (*exec->cmd)->args[1] == NULL)
		export_only((exec->env));
    else if(ft_strcmp(cmd, "export") == 0)
        export_w_error(exec, newnode, cmd);

}

void    export_w_error(t_exec *exec, t_env *newnode, char *cmd)
{
    int i;
    
    i = 1;
    char *tmp;
    char *temp;
    char **all;
    
    all = (*exec->cmd)->args;
    while(all[i])
    {
        temp = search_and_stop(cmd, '=');
        if(ft_strncmp(temp, (*exec->env)->variable, ft_strlen((*exec->env)->variable) == 0))
        {
            tmp = ft_strchr(cmd, '=');
            newnode->value = ft_strdup(tmp);
            newnode->variable = search_and_stop(cmd, '=');
        }    
        else 
        {
            newnode = ft_lstnew_for_env(all[i]);
        }
        ft_lstadd_back((exec->env), newnode);
        i++;
    }
}

void    export_only(t_env **env)
{
	t_env *tmp;
	
    sort_str(env);
    tmp = *env;
    while(tmp)
    {
        if(tmp->value == NULL)
            printf("export %s\n", tmp->variable);
        else
            printf("export %s=\"%s\"\n", tmp->variable, tmp->value);

		tmp = tmp->next;
    }
}

/*
si :
export test -> export seulement la variabe mais si on fait env, ne s'affiche pas
si export test= -> export la variable + dans le env s'affiche ; test=, et dans export -> test=""
si export=bjr -> export la variable + dans le env s'affiche ; test=bjr, et dans export -> test="bjr"

faire un dup du env et le mettre dans un tab pour l'export
*/
 
