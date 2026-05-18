/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:53:30 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/17 16:57:58 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr;
	unsigned const char	*ptr1;

	ptr = (unsigned char *)dst;
	ptr1 = (unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (ptr > ptr1)
	{
		i = n;
		while (i--)
			ptr[i] = ptr1[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			ptr[i] = ptr1[i];
			i++;
		}
	}
	return (dst);
}

/*int main(void)
{
	char src[] = "helloWorld";
	char src1[] = "helloWorld";
	// char dst[100];

	size_t n = 5;
	ft_memmove(src + 2, src, n);
	memmove(src1 + 2, src1, n);
	printf("%s\n", src);
	printf("%s\n", src1);

}*/
