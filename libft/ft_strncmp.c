/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:53:46 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/17 17:22:49 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n && s1[i] && s2[i] && s1[i] == s2[i]))
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
// int main(int argc, char **argv)
// {
//     if (argc >= 1)
//     {
//         printf("%d\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
//         printf("%d\n", strncmp(argv[1], argv[2], atoi(argv[3])));
//     }
// }