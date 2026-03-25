/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:22:51 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 15:57:12 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"

static int	check_n_flag(char *s)
{
	int	i;

	if (s[0] != '-' || s[1] != 'n')
		return (1);
	i = 2;
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (1);
	return (0);
}

int	builtin_echo(char **argv)
{
	int	i;
	int	n_flag;

	if (!argv[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	n_flag = 0;
	while (argv[i] && check_n_flag(argv[i]) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!n_flag)
		write(1, "\n", 1);
	return (0);
}
