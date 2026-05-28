#include "minishell.h"

char	*ft_strchr_echo(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] && s[i] == (char)c)
			return ((char *)&s[i]+2);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]+2);
	return (NULL);
}

int c_strrcmp(char *str, char b)
{
    int i;
    
    i = 0;
	while(str[i])
		i++;
    while(i >= 0)
    {
        if(str[i] == b)
            return (0);
        i--;
    }
    return (1);
}
