/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:15:38 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/09 12:52:00 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "libft.h"
#include "utils.h"

int	builtin_env(t_general *general, char **argv)
{
	t_env	*temp;

	if (argv && argv[1])
	{
		write3(general, "env: '", argv[1], "': No such file or directory\n");
		return (127);
	}
	temp = general->env;
	while (temp)
	{
		if (temp->exported == 1)
		{
			ft_putstr_fd(temp->key, 1);
			write(1, "=", 1);
			if (temp->value)
				ft_putstr_fd(temp->value, 1);
			write(1, "\n", 1);
		}
		temp = temp->next;
	}
	return (0);
}
