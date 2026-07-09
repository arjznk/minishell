#include "minishell.h"

// void    expand_var(t_exec *exec)
// {
//     char *line;
//     t_env *tmp;
//     int i;

//     tmp = (*exec->env);
//     line = ft_strchr((*exec->cmd)->args[1], '$');
//     i = 0;
//     while(tmp)
//     {
//         if(ft_strcmp(line, tmp->variable) == 0)
//             printf("%s\n", tmp->value);
//         tmp = tmp->next;
//         i++;
//     }
// }

void    exit_code(t_exec *exec)
{
    if(ft_strcmp((*exec->cmd)->args[1], "$?") == 0)
        printf("%d\n", exec->status);
}

char    *get_var_name(char *str, int *i)
{
    int start;

    (*i)++;
    start = *i;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    (*i)--;
    return (ft_substr(str, start, *i - start + 1));
}

char    *get_env_value(char *var_name, t_env *env)
{
    while (env)
    {
        if (ft_strcmp(var_name, env->variable) == 0)
            return (env->value);
        env = env->next;
    }
    return ("");
}

char    *expand_var2(char *str, int *i, char *result, t_exec *exec)
{
    char    *var_name;
    char    *value;
    char    *new_result;

    if (str[*i + 1] == '?')
    {
        value = ft_itoa(exec->status);
        new_result = ft_strjoin(result, value);
        free(result);
        free(value);
        (*i)++;
        return (new_result);
    }
    if (!str[*i + 1] || str[*i + 1] == ' ')
        return (join_char(result, '$'));
    var_name = get_var_name(str, i);
    value = get_env_value(var_name, *(exec->env));
    new_result = ft_strjoin(result, value);
    free(result);
    free(var_name);
    return (new_result);
}
