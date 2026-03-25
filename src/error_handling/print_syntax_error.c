/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:34:05 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 19:25:08 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"
#include "utils.h"

int	print_syntax_error(t_general *general, const char *token)
{
	write3(general, \
		"minishell: syntax error near unexpected token `", token, "'\n");
	general->exit_status = 2;
	return (1);
}

static int	print_ampersand_error(t_general *general, char *line, int i)
{
	if (line[i + 1] == '&')
		return (print_syntax_error(general, "&&"));
	return (print_syntax_error(general, "&"));
}

int	print_syntax_error_for_char(t_general *general, char *line, int i)
{
	if (line[i] == '|' || line[i] == '<' || line[i] == '>')
	{
		if (line[i + 1] == line[i])
		{
			if (line[i] == '|')
				return (print_syntax_error(general, "||"));
			if (line[i] == '<')
				return (print_syntax_error(general, "<<"));
			return (print_syntax_error(general, ">>"));
		}
		if (line[i] == '|')
			return (print_syntax_error(general, "|"));
		if (line[i] == '<')
			return (print_syntax_error(general, "<"));
		return (print_syntax_error(general, ">"));
	}
	if (line[i] == ')')
		return (print_syntax_error(general, ")"));
	if (line[i] == '&')
		return (print_ampersand_error(general, line, i));
	return (0);
}
