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
    else if(ft_strcmp(cmd, "export") == 0)
    {
        export_w_error(exec, newnode);
        exec->status = 0;
    }
}

int    export_error(t_exec *exec)
{
    int i;

    i = 0;
    while((*exec->cmd)->args[1][i])
    {
        if(c_strcmp((*exec->cmd)->args[1], '_') == 0)
            i++;
        else if((ft_isalpha(((*exec->cmd)->args[1][i]) == 1)) || (ft_isalpha((*exec->cmd)->args[1][i]) == 1 && (*exec->cmd)->args[1][i+1] == 0))
        {
            export_return(exec);
            return (1);
        }
        else if(c_strcmp((*exec->cmd)->args[1], '!') == 0)
        {
            printf("minishell: %s: event not found\n", (*exec->cmd)->args[1]);
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
    char *temp;
    int found;
    int i;
    
    i = 1;
    while((*exec->cmd)->args[i])
    {
        temp = search_and_stop((*exec->cmd)->args[i], '=');
        tp = (*exec->env);
        found = 0;
        while(tp)
        {
            if(ft_strcmp(temp, tp->variable) == 0)
            {
                exist_var(exec, i, tp, temp);
                found = 1;
                break;
            }
            tp = tp->next;
        }
        if(!found)
            add_to_env(exec, newnode, i);
        i++;
    }
}

void    exist_var(t_exec *exec, int i, t_env *tp, char *temp)
{
    char *tmp;

    tmp = ft_strchr((*exec->cmd)->args[i], '=');
    free(tp->value);
    if(tmp != NULL)
        tp->value = ft_strdup(tmp);
    tp->variable = temp;
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

void   export_return(t_exec *exec)
{
    printf("minishell: %s: not a valid identifer\n", (*exec->cmd)->args[1]);
    exec->status = 1;
}