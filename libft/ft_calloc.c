/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:32:52 by rijebbar          #+#    #+#             */
/*   Updated: 2025/11/19 10:27:55 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*int main (void)
{
	int *tab;
	int i;
	int *tab2;

	tab = ft_calloc(5, sizeof(int)); 
	tab2 = calloc(5, sizeof(int));

	for (i = 0; i < 5; i++)
		printf("tab[%d] = %d\n", i, tab[i]);

	for (i = 0; i < 5; i++)
		printf("tab2[%d] = %d\n", i, tab2[i]);

	free(tab);
	free(tab2);
	return (0);
}*/
