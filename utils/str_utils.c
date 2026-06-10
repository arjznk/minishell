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

char	*search_and_return(char *str, char c)
{
	char *dest;
	int i;

	i = 0;
	dest = malloc(sizeof(char) * ft_strlen(str));
	if(!dest)
		return (NULL);
	while(str[i])
	{
		if(str[i] == c)
		{
			i++;
			dest[i] = str[i];
		}
		i++;
	}
	dest[i] = '\0';
	return(dest);
}