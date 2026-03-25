/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:16:55 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 17:30:08 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "libft.h"
#include "utils.h"

int	find_open_bracket(char *line, int pos)
{
	int	depth;

	depth = 0;
	while (pos >= 0)
	{
		if (line[pos] == ')')
			depth++;
		else if (line[pos] == '(')
		{
			depth--;
			if (depth == 0)
				return (pos);
		}
		pos--;
	}
	return (-1);
}

static int	skip_quotes_backwards(char *line, int position)
{
	if (line[position] == '"')
	{
		position--;
		while (position > -1 && line[position] != '"')
			position--;
	}
	else if (line[position] == '\'')
	{
		position--;
		while (position > -1 && line[position] != '\'')
			position--;
	}
	return (position);
}

int	find_operator(char *line, char *op1, char *op2, int op_len)
{
	int	pos;

	pos = ft_strlen(line) -1;
	while (pos >= 0)
	{
		if (line[pos] == '"' || line[pos] == '\'')
			pos = skip_quotes_backwards(line, pos);
		else if (line[pos] == ')')
			pos = find_open_bracket(line, pos);
		if (op2 != NULL)
		{
			if (pos - (op_len - 1) != -1 && \
			(ft_strncmp(&line[pos - (op_len - 1)], op1, op_len) == 0 || \
			ft_strncmp(&line[pos - (op_len - 1)], op2, op_len) == 0))
				return (pos - (op_len - 1));
		}
		else
		{
			if (pos - (op_len - 1) != -1 && \
			ft_strncmp(&line[pos - (op_len - 1)], op1, op_len) == 0)
				return (pos - (op_len - 1));
		}
		pos--;
	}
	return (-1);
}
