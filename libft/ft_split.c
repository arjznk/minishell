/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:00:05 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/19 14:00:05 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_word(char const *str, char c)
{
	size_t		i;
	size_t		word;

	i = 0;
	word = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			word++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (word);
}

size_t	len_word(char const *str, char c)
{
	size_t		lenword;

	lenword = 0;
	while (str[lenword] && str[lenword] != c)
		lenword++;
	return (lenword);
}

static void	ft_cpy(char const *s, char *s1, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
}

static char	**ft_free(char **s)
{
	int		word;

	word = 0;
	while (s[word])
	{
		free(s[word]);
		word++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**s1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s1 = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!s1 || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		s1[j] = malloc(sizeof(char) * (len_word(s + i, c) + 1));
		if (s1[j] == NULL)
			return (ft_free(s1));
		ft_cpy(s + i, s1[j++], c);
		while (s[i] != c && s[i])
			i++;
	}
	s1[j] = NULL;
	return (s1);
}

//  int	main(int argc, char **argv)
// {
// 	size_t i = 0;
//  	char **s1 = ft_split(argv[1], argv[2][0]);
// 	if (argc >= 1)
// 	{
//  		while (s1[i])
// 		{
//  			printf("%s\n", s1[i]);
//  			i++;
// 		}
// 	}
// 	return (0);
// }
