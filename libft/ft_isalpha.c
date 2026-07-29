/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rijebbar <rijebbar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:34:11 by rijebbar          #+#    #+#             */
/*   Updated: 2026/07/29 13:05:58 by rijebbar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(char *str)
{
	int c;
	
	c = 0;
	while(str[c])
	{
		 if (!((str[c] == '_') || (str[c] >= 'a' && str[c] <= 'z') || (str[c] >= 'A' && str[c] <= 'Z') || (c > 0 && str[c] >= '0' && str[c] <= '9')))
            return (0);
		c++;
	}
	return (1);
}

// int main(void)
// {
//     int c = 'a'
//     printf("%d\n", ft_isalpha(c));
// }