#include "minishell.h"

void	ft_export(t_exec *exec)
{
	t_env	*newnode;
	char	*cmd;

    cmd = exec->tmp->args[0];
    newnode = malloc(sizeof(t_env));
    if(!newnode)
		return ;
    if(exec->tmp->args[0] && exec->tmp->args[1] == NULL)
        export_only((exec));
    else if(export_error(exec) != 0 && exec->tmp->args[1])
            return;
    else if(ft_strcmp(cmd, "export") == 0)
    {
        export_w_error(exec, newnode);
        exec->status = 0;
    }
}

int	export_error(t_exec *exec)
{
	int		i;
	char	*var;

    i = 0;
    var = search_and_stop(exec->tmp->args[1], '=');
    while((var[i]))
    {
        if(compar_char(var[i], '_') == 0)
            i++;
        if(ft_isalpha(var[i]) == 0 || ft_isdigit(var) == 0)
        {
            printf("minishell: export: `%s': not a valid identifier\n", exec->tmp->args[1]);
            exec->status = 1;
            return (1);
        }
        i++;
    }
    return(0);  
}

void	export_w_error(t_exec *exec, t_env *newnode)
{
    t_env *tp;
    char *temp;
    int found;
    int i;
    
    i = 1;
    while(exec->tmp->args[i])
    {
        temp = search_and_stop(exec->tmp->args[i], '=');
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

void	exist_var(t_exec *exec, int i, t_env *tp, char *temp)
{
	char	*tmp;

    tmp = ft_strchr(exec->tmp->args[i], '='); 
    if(tmp != NULL)
    {
        free(tp->value);
        tp->value = ft_strdup(tmp);
    }
    free(temp);
}

void	export_only(t_exec *exec)
{
	t_env	*tmp;

	sort_str((exec->env));
	tmp = (*exec->env);
	while (tmp)
	{
		if (tmp->value == NULL)
			printf("export %s\n", tmp->variable);
		else
			printf("export %s=\"%s\"\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
	exec->status = 0;
}

void	export_return(t_exec *exec)
{
    printf("minishell: %s: not a valid identifer\n", exec->tmp->args[1]);
    exec->status = 1;
}