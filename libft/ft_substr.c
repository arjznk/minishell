/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 10:44:53 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/17 15:55:43 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		len = 0;
	}
	if (len > ft_strlen(s) - start)
	{
		len = ft_strlen(s) - start;
	}
	s1 = malloc(sizeof(char) * len + 1);
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
/*int main(void)
{
	char s[20] = "hello";
	unsigned int start = 2;
	size_t len = 9;

	printf("%s\n", ft_substr(s, start, len));
}*/