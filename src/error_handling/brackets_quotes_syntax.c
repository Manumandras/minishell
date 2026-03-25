/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets_quotes_syntax.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:55:47 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 19:29:20 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "utils.h"
#include "error_handling.h"

int	unclosed_quotes(t_general *general, char *line)
{
	int	i;
	int	quote_char;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote_char = line[i];
			i++;
			while (line[i] && line[i] != quote_char)
				i++;
			if (line[i] == '\0')
			{
				general->exit_status = 2;
				write(2, "minishell: syntax error: unclosed quotes\n", 41);
				return (1);
			}
		}
		if (line[i])
			i++;
	}
	return (0);
}

static int	update_bracket_state(t_general *general, \
	char *line, int *i, int *depth)
{
	if (line[*i] == '"' || line[*i] == '\'')
	{
		*i = skip_quotes(line, *i, line[*i]);
		return (0);
	}
	if (line[*i] == '(')
		(*depth)++;
	else if (line[*i] == ')')
	{
		(*depth)--;
		if (*depth < 0)
			return (print_syntax_error(general, ")"));
	}
	(*i)++;
	return (0);
}

int	unclosed_brackets(t_general *general, char *line)
{
	int	i;
	int	depth;

	i = 0;
	depth = 0;
	while (line[i])
	{
		if (update_bracket_state(general, line, &i, &depth) != 0)
			return (1);
	}
	if (depth != 0)
		return (print_syntax_error(general, "("));
	return (0);
}
