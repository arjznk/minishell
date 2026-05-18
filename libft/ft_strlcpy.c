/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:53:42 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/17 17:11:36 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz == 0)
		return (ft_strlen(src));
	if (siz)
	{
		while (i < siz - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

// int main()
// {
// 	char dst1[20] = "Hello";
// 	const char src[20] = "helloo";

// 	size_t siz1 = 100;

// 	printf("%zu\n", ft_strlcpy(dst1, src, siz1));
// }