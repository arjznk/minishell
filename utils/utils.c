#include "minishell.h"

char *search_and_stop(char *str, char c)
{
    int i;
    char *dest;
    
    i = 0;
    dest = malloc(sizeof(char) * ft_strlen(str));
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

char	*ft_strchr_value(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == (char)c)
			return ((char *)&s[i] + 1);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i] + 1);
	return (NULL);
}