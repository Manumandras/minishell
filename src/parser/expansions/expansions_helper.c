/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnieders <jnieders@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:04:46 by jnieders          #+#    #+#             */
/*   Updated: 2025/12/08 11:38:24 by jnieders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int	update_quote_mode(char c, char *mode)
{
	if (*mode == 0)
	{
		if (c == '\'' || c == '"')
		{
			*mode = c;
			return (1);
		}
	}
	else if (*mode == '\'')
	{
		if (c == '\'')
		{
			*mode = 0;
			return (1);
		}
	}
	else if (*mode == '"')
	{
		if (c == '"')
		{
			*mode = 0;
			return (1);
		}
	}
	return (0);
}

int	count_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (argv[i])
		i++;
	return (i);
}

int	count_match_list(t_match *node)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}
