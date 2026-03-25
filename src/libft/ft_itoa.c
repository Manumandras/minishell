/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:54:27 by jnieders          #+#    #+#             */
/*   Updated: 2025/06/05 13:09:23 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrev(char *s)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
	return (s);
}

static int	ft_len_n(long long n)
{
	long long	c;

	c = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n > 0)
	{
		n = n / 10;
		c++;
	}
	return ((int)c);
}

static void	ft_itoa_put(char *dest, long long n)
{
	long long	i;

	i = 0;
	if (n == 0)
		dest[i] = '0';
	while (n > 0)
	{
		dest[i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char		*ptr;
	long long	nb;
	int			len_n;

	nb = n;
	len_n = ft_len_n(nb);
	if (nb < 0)
	{
		nb = -nb;
		ptr = malloc(sizeof(char) * (len_n + 2));
		if (!ptr)
			return (NULL);
		ft_itoa_put(ptr, nb);
		ptr[len_n] = '-';
		ptr[len_n + 1] = '\0';
		ft_strrev(ptr);
		return (ptr);
	}
	ptr = malloc(sizeof(char) * (len_n + 1));
	if (!ptr)
		return (NULL);
	ft_itoa_put(ptr, nb);
	ptr[len_n] = '\0';
	ft_strrev(ptr);
	return (ptr);
}
