
#include <string.h>
#include <stdio.h>

// char	*ft_strchr(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] && s[i] == (char)c)
// 			return ((char *)&s[i]);
// 		i++;
// 	}
// 	if ((char)c == '\0')
// 		return ((char *)&s[i]);
// 	return (NULL);
// }
// int main()
// {
// 	const char s[] = "GJS_DEBUG_TOPICS=JS ERROR;JS LOG";
// 	int c = '=';

// 	printf("%s\n", ft_strchr(s, c));
// 	// printf("%s\n", strchr(s, c));
// }

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	if (c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int main (void)
{
	const char s[] = "GJS_DEBUG_TOPICS=JS ERROR;JS LOG";
	int c = '=';

	printf("%s\n", ft_strrchr(s, c));
	// printf("%s\n", strrchr(s, c));
}