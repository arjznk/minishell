void    ft_unset(char *str, t_env **env)
{
    char *line;

    line = ft_strchr(str, ' ');
    if(ft_strncmp(str, "unset", 5) == 0)
    {
        t_env *tmp;
        t_env *prev;
        t_env *to_free;

        prev = NULL;
        tmp = *env;
        while(tmp)
        {
            if(ft_strncmp(tmp->variable, line, ft_strlen(line)) == 0)
            {
                if(prev == NULL)
                {
                    to_free = tmp;
                    *env = tmp->next;
                    free(to_free);
                    break;
                }
                else
                {
                    to_free = tmp;
                    prev->next = tmp->next;
                    free(to_free);
                    break;
                }
            }
            prev = tmp;
            tmp = tmp->next;
        }
    }
}