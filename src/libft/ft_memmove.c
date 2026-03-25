/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 12:35:25 by jnieders          #+#    #+#             */
/*   Updated: 2025/06/03 13:17:28 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptrd;
	unsigned char	*ptrs;
	size_t			i;

	ptrd = (unsigned char *)dest;
	ptrs = (unsigned char *)src;
	if (!src && !dest)
		return (dest);
	if (src < dest)
	{
		while (n > 0)
		{
			ptrd[n - 1] = ptrs[n - 1];
			n--;
		}
	}
	else
	{
		i = -1;
		while (++i < n)
			ptrd[i] = ptrs[i];
	}
	return (dest);
}
