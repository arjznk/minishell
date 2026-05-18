/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:20:22 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/19 13:35:03 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*s2;
	int		start;
	int		end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = (ft_strlen(s1) - 1);
	while (s1[start] && char_in_set(s1[start], set))
		start++;
	while (start <= end && char_in_set(s1[end], set))
		end--;
	s2 = malloc(sizeof(char) * (end - start) + 2);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (start <= end)
		s2[i++] = s1[start++];
	s2[i] = '\0';
	return (s2);
}
/*int	main(int argc, char **argv)
{
	if (argc >= 1)
		printf("%s\n", ft_strtrim(argv[1], argv[2]));
}*/