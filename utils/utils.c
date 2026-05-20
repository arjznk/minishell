#include "minishell.h"

char *search_and_stop(char *str, char c)
{
    int i = 0;
    char *dest = malloc(sizeof(char) * ft_strlen(str));
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