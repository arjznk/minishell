/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:53:39 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/13 20:55:29 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (siz == 0)
		return (ft_strlen(src));
	while (dst[i] && i < siz)
		i++;
	j = i;
	while (src[i - j] && i < siz - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (j < siz)
		dst[i] = '\0';
	return (j + ft_strlen(src));
}
/*int main(void)
{
	char dst1[30] = "hello";
	char dst2[30] = "hello";
	const char *src = "hry";
	size_t siz = 30;

	size_t r1 = ft_strlcat(dst1, src, siz);
	size_t r2 = strlcat(dst2, src, siz);

	printf("ft_strlcat : dst = %s, return (= %zu\n", dst1, r1));
	printf("strlcat : dst = %s, return (= %zu\n", dst2, r2));
}*/