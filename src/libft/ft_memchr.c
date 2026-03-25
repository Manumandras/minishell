/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:44:01 by jnieders          #+#    #+#             */
/*   Updated: 2025/06/03 11:02:55 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptrs;
	unsigned char	ptrc;
	size_t			i;

	ptrs = (unsigned char *)s;
	ptrc = (unsigned char )c;
	i = 0;
	while (i < n)
	{
		if (ptrs[i] == ptrc)
			return (&ptrs[i]);
		i++;
	}
	return (0);
}
