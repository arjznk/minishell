/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:53:28 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/17 16:56:28 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	*ptr1;

	ptr = (unsigned char *)dest;
	ptr1 = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		ptr[i] = ptr1[i];
		i++;
	}
	return (dest);
}
/*int main(void)
{
	char dest[100];
	char src[100] = "hello";
	size_t n = 5;

	ft_memcpy(dest, src, n);
	memcpy(dest, src, n);
	printf("%s\n", dest);
	printf("%s\n", dest);
}*/