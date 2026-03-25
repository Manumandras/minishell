/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmittelb <mmittelb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 13:53:45 by mmittelb          #+#    #+#             */
/*   Updated: 2025/12/08 19:28:31 by mmittelb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "error_handling.h"

static int	handle_redir_at(char *line, int i, t_general *general)
{
	int	j;

	j = i + 1;
	if (line[j] == line[i])
		j++;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[j] == '\0')
		return (print_syntax_error(general, "newline"));
	if (line[j] == '|' || line[j] == '<' || line[j] == '>' || line[j] == '&'
		|| line[j] == ')' )
		return (print_syntax_error_for_char(general, line, j));
	return (0);
}

int	check_redir_syntax(t_general *general, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			i = skip_quotes(line, i, line[i]);
			continue ;
		}
		if (line[i] == '<' || line[i] == '>')
		{
			if (handle_redir_at(line, i, general))
				return (1);
		}
		if (line[i])
			i++;
	}
	return (0);
}
