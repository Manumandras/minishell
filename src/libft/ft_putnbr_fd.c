/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:46:24 by jnieders          #+#    #+#             */
/*   Updated: 2025/06/03 10:58:10 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd_rec(long nb, int fd)
{
	char	c;

	if (nb > 0)
	{
		ft_putnbr_fd_rec(nb / 10, fd);
		c = (nb % 10) + 48;
		write(fd, &c, 1); 
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nb;

	nb = n;
	if (nb == 0)
	{
		c = '0';
		write(fd, &c, 1);
	}
	else if (nb < 0)
	{
		c = '-';
		write(fd, &c, 1);
		nb = nb * -1;
		ft_putnbr_fd_rec(nb, fd);
	}
	else
		ft_putnbr_fd_rec(nb, fd);
}
