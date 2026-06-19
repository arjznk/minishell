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
        export_only((exec));
    else if(ft_strcmp(cmd, "export") == 0)
        export_w_error(exec, newnode);

}

void    export_w_error(t_exec *exec, t_env *newnode)
{
    t_env *tp;
    char *tmp;
    char *temp;
    int found;
    
    tp = (*exec->env);
    found = 0;
    temp = search_and_stop((*exec->cmd)->args[1], '=');
    while(tp)
    {
        if(ft_strcmp(temp, tp->variable) == 0)
        {
            tmp = ft_strchr((*exec->cmd)->args[1], '=');
            free(tp->value);
            tp->value = ft_strdup(tmp);
            tp->variable = temp;
            found = 1;
        }
        tp = tp->next;
    }
    if(!found)
    {
        newnode = ft_lstnew_for_env((*exec->cmd)->args[1]);
        ft_lstadd_back((exec->env), newnode);
    }
}

void    export_only(t_exec *exec)
{
	t_env *tmp;
	
    sort_str((exec->env));
    tmp = (*exec->env);
    while(tmp)
    {
        if(tmp->value == NULL)
            printf("export %s\n", tmp->variable);
        else
            printf("export %s=\"%s\"\n", tmp->variable, tmp->value);

		tmp = tmp->next;
    }
}

 
