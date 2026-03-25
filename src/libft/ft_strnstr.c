/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:21:47 by jnieders          #+#    #+#             */
/*   Updated: 2025/06/05 13:05:30 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)&big[0]);
	while (i < len && big[i])
	{
		j = 0;
		while ((big[i] == little[j]) && little[j] && (i < len))
		{
			i++;
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i - j]);
		i = i - j;
		i++;
	}
	return (0);
}
