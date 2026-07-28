/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:34:44 by rijebbar          #+#    #+#             */
/*   Updated: 2025/07/12 15:55:34 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (((s1[i] == s2[i]) && (s1[i]) && (s2[i])))
		i++;
	return (s1[i] - s2[i]);
}

/*#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc > 1)
		printf("%d", ft_strcmp(argv[1], argv[2]));
}*/
