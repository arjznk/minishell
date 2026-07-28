/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:44:06 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/17 09:44:06 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*s3;

	i = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = i;
	while (s2[i - j])
	{
		s3[i] = s2[i - j];
		i++;
	}
	s3[i] = '\0';
	return (s3);
}
/*int main (int argc, char **argv)
{
	if (argc >= 1)
		printf("%s\n", ft_strjoin(argv[1], argv[2]));
}*/ 