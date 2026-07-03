#include "minishell.h"

void    ft_export(t_exec *exec)
{
    t_env *newnode;
    char *cmd;

    cmd = (*exec->cmd)->args[0];
    newnode = malloc(sizeof(t_env));
    if(!newnode)
		return ;
	if((*exec->cmd)->args[0] && (*exec->cmd)->args[1] == NULL)
        export_only((exec));
    else if(export_error(exec) != 0 && (*exec->cmd)->args[1])
        return;
    else if(ft_strcmp(cmd, "export") == 0 && (*exec->cmd)->args[1])
        export_w_error(exec, newnode);
}

int    export_error(t_exec *exec)
{
    int i;

    i = 0;
    while((*exec->cmd)->args[1][i])
    {
        if(c_strcmp((*exec->cmd)->args[1], '!') == 0)
        {
            printf("minishell: %s: event not found\n", (*exec->cmd)->args[1]);
            exec->status = 1;
            return (1);
        }
        if(ft_isalpha((*exec->cmd)->args[1][i]) == 0)
        {
            printf("minishell: export: `%s': not a valid identifier\n", (*exec->cmd)->args[1]);
            exec->status = 1;
            return (1);
        }
        i++;
    }
    return(0);  
}

void    export_w_error(t_exec *exec, t_env *newnode)
{
    t_env *tp;
    char *tmp;
    char *temp;
    int found;
    int i;
    
    i = 1;
    tp = (*exec->env);
    found = 0;
    while(tp && (*exec->cmd)->args[i])
    {
        temp = search_and_stop((*exec->cmd)->args[i], '=');
        if(ft_strcmp(temp, tp->variable) == 0)
        {
            tmp = ft_strchr((*exec->cmd)->args[i], '=');
            free(tp->value);
            tp->value = ft_strdup(tmp);
            tp->variable = temp;
            found = 1;
        }
        if(!found)
        {
            newnode = ft_lstnew_for_env((*exec->cmd)->args[i]);
            ft_lstadd_back((exec->env), newnode);
        }
        tp = tp->next;
        i++;
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
    exec->status = 0;
}

 
